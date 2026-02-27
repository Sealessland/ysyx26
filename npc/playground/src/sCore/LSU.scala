package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

// -----------------------------------------------------------------------------
// 传递给写回级 (WB) 的负载信息
// -----------------------------------------------------------------------------
class MEM_WB_Bundle(implicit p: CoreConfig) extends CoreBundle {
  val inst      = UInt(32.W)        // 透传的原始指令
  val rfData    = UInt(xlen.W)      // 将要写回通用寄存器的数据
  val pc        = UInt(vaddrBits.W) // 顺着流水线传下来的原 PC (可供测试观测)
  
  // 透传上一级控制信号
  val rdaddr    = UInt(5.W)
  val mdTarget  = WbTarget() // To avoid collision, I just remembered it was wbTarget
  val wbTarget  = WbTarget()
  val halt      = Bool()

  // CSR 相关
  val csrWdata  = UInt(xlen.W)
  val csrAddr   = UInt(12.W)
  val csrOp     = CsrOp()
  
  // 访存状态标志透传，供 WBU 输出 `wb_is_store` 标志
  val memCmd    = MemCmd()
}

// -----------------------------------------------------------------------------
// LSU 的 IO 接口
// -----------------------------------------------------------------------------
class LSUIO(implicit p: CoreConfig) extends CoreBundle {
  val in  = Flipped(if (isSingleCycle) new EX_MEM_Bundle else Decoupled(new EX_MEM_Bundle))
  val out = if (isSingleCycle) Output(new MEM_WB_Bundle) else Decoupled(new MEM_WB_Bundle)
  val axi = if (p.lsu.lsuMode == "axiLite" || p.lsu.lsuMode == "axi4")
    Some(new AxiLiteMasterIO(p.paddrBits, p.xlen)) else None
}

// -----------------------------------------------------------------------------
// DPI-C Blackbox 对外部存储进行访问的接口声明
// 参数化控制输入输出位宽
// -----------------------------------------------------------------------------
class DPIC_LSU(addrBits: Int, dataBits: Int) extends ExtModule(Map(
  "ADDR_WIDTH" -> addrBits,
  "DATA_WIDTH" -> dataBits
)) {
  val io = IO(new Bundle {
    val clk    = Input(Clock())
    val en     = Input(Bool())
    val cmd    = Input(Bool()) // 1 for write, 0 for read
    val addr   = Input(UInt(addrBits.W))
    val wdata  = Input(UInt(dataBits.W))
    val len    = Input(UInt(8.W))
    val rdata  = Output(UInt(dataBits.W))
  })
  
  override val desiredName = "DPIC_LSU"
  addPath("playground/src/sCore/utils/vsrc/DPIC_LSU.sv")
}

// -----------------------------------------------------------------------------
// 访存单元核心模块 (LSU)
// -----------------------------------------------------------------------------
class LSU()(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new LSUIO)

  if (p.lsu.lsuMode == "axiLite" || p.lsu.lsuMode == "axi4") {
    require(!isSingleCycle, "AXI(-Lite) LSU requires decoupled pipeline interface")

    val axi = io.axi.get
    val inDec  = io.in.asInstanceOf[DecoupledIO[EX_MEM_Bundle]]
    val outDec = io.out.asInstanceOf[DecoupledIO[MEM_WB_Bundle]]

    val busBytes = (xlen / 8)
    val byteOffBits = log2Ceil(busBytes)
    val addrAlignMask = Cat(Fill(p.paddrBits - byteOffBits, 1.U), 0.U(byteOffBits.W))

    val sIdle :: sSend :: sWait :: sResp :: Nil = Enum(4)
    val state = RegInit(sIdle)
    val reqReg = Reg(new EX_MEM_Bundle)
    val rawRdataReg = Reg(UInt(xlen.W))
    val awSent = RegInit(false.B)
    val wSent  = RegInit(false.B)
    val isWrite = RegInit(false.B)

    // 默认信号
    val addrSel = reqReg.aluOut(p.paddrBits - 1, 0)
    axi.aw.bits.addr := addrSel & addrAlignMask
    axi.aw.bits.prot := 0.U
    axi.w.bits.data  := reqReg.rs2Data
    axi.w.bits.strb  := 0.U
    axi.ar.bits.addr := addrSel & addrAlignMask
    axi.ar.bits.prot := 0.U

    axi.aw.valid := false.B
    axi.w.valid  := false.B
    axi.ar.valid := false.B
    axi.b.ready  := false.B
    axi.r.ready  := false.B

    inDec.ready := (state === sIdle)

    when(state === sIdle && inDec.fire) {
      reqReg := inDec.bits
      isWrite := inDec.bits.memCmd === MemCmd.WRITE
      awSent := false.B
      wSent  := false.B
      when(inDec.bits.memCmd === MemCmd.READ || inDec.bits.memCmd === MemCmd.WRITE) {
        state := sSend
      } .otherwise {
        state := sResp
      }
    }

    when(state === sSend) {
      when(isWrite) {
        val memSize = reqReg.memSize
        val memByteLen = MuxLookup(memSize, 4.U(8.W))(Seq(
          MemSize.B -> 1.U,
          MemSize.H -> 2.U,
          MemSize.W -> 4.U,
          MemSize.D -> 8.U
        ))
        val byteOffset = reqReg.aluOut(byteOffBits - 1, 0)
        val shift = (byteOffset << 3).asUInt
        val strbMaskWide = ((1.U((busBytes + 1).W)) << memByteLen) - 1.U
        val strbShifted = (strbMaskWide << byteOffset)(busBytes - 1, 0)
        val wdataShifted = reqReg.rs2Data << shift

        axi.aw.valid := !awSent
        axi.w.valid  := !wSent
        axi.w.bits.data := wdataShifted
        axi.w.bits.strb := strbShifted

        val awDone = awSent || axi.aw.fire
        val wDone  = wSent  || axi.w.fire
        when(axi.aw.fire) { awSent := true.B }
        when(axi.w.fire)  { wSent  := true.B }
        when(awDone && wDone) {
          state := sWait
        }
      } .otherwise {
        axi.ar.valid := true.B
        when(axi.ar.fire) {
          state := sWait
        }
      }
    }

    when(state === sWait) {
      when(isWrite) {
        axi.b.ready := true.B
        when(axi.b.fire) {
          state := sResp
        }
      } .otherwise {
        axi.r.ready := true.B
        when(axi.r.fire) {
          rawRdataReg := axi.r.bits.data
          state := sResp
        }
      }
    }

    // 读数据偏移处理
    val shiftAmount = MuxLookup(reqReg.memSize, 0.U(6.W))(Seq(
      MemSize.B -> Cat(reqReg.aluOut(1, 0), 0.U(3.W)).pad(6),
      MemSize.H -> Cat(reqReg.aluOut(1), 0.U(4.W)).pad(6),
      MemSize.W -> (if (xlen == 64) Cat(reqReg.aluOut(2), 0.U(5.W)).pad(6) else 0.U(6.W)),
      MemSize.D -> 0.U(6.W)
    ))
    val shiftedRdata = rawRdataReg >> shiftAmount

    val rfData = WireInit(0.U(xlen.W))
    when(reqReg.memCmd === MemCmd.READ) {
      if (xlen == 64) {
        rfData := MuxLookup(reqReg.memSize, shiftedRdata)(Seq(
          MemSize.B -> Mux(reqReg.memSign, Cat(Fill(56, shiftedRdata(7)), shiftedRdata(7, 0)), Cat(Fill(56, 0.U), shiftedRdata(7, 0))),
          MemSize.H -> Mux(reqReg.memSign, Cat(Fill(48, shiftedRdata(15)), shiftedRdata(15, 0)), Cat(Fill(48, 0.U), shiftedRdata(15, 0))),
          MemSize.W -> Mux(reqReg.memSign, Cat(Fill(32, shiftedRdata(31)), shiftedRdata(31, 0)), Cat(Fill(32, 0.U), shiftedRdata(31, 0))),
          MemSize.D -> shiftedRdata
        ))
      } else {
        rfData := MuxLookup(reqReg.memSize, shiftedRdata)(Seq(
          MemSize.B -> Mux(reqReg.memSign, Cat(Fill(24, shiftedRdata(7)), shiftedRdata(7, 0)), Cat(Fill(24, 0.U), shiftedRdata(7, 0))),
          MemSize.H -> Mux(reqReg.memSign, Cat(Fill(16, shiftedRdata(15)), shiftedRdata(15, 0)), Cat(Fill(16, 0.U), shiftedRdata(15, 0))),
          MemSize.W -> shiftedRdata
        ))
      }
    } .otherwise {
      rfData := reqReg.aluOut
    }

    val msgOut = Wire(new MEM_WB_Bundle)
    msgOut          := DontCare
    msgOut.inst     := reqReg.inst
    msgOut.rfData   := rfData
    msgOut.pc       := reqReg.pc
    msgOut.rdaddr   := reqReg.rdaddr
    msgOut.wbTarget := reqReg.wbTarget
    msgOut.halt     := reqReg.halt
    msgOut.csrWdata := reqReg.csrWdata
    msgOut.csrAddr  := reqReg.csrAddr
    msgOut.csrOp    := reqReg.csrOp
    msgOut.memCmd   := reqReg.memCmd

    outDec.valid := (state === sResp)
    outDec.bits  := msgOut
    when(outDec.fire) {
      state := sIdle
    }
  } else {
    // 提取进来的执行级结果和访存信号
    val inValid = if (isSingleCycle) true.B else io.in.asInstanceOf[DecoupledIO[EX_MEM_Bundle]].valid
    val inData  = if (isSingleCycle) io.in.asInstanceOf[EX_MEM_Bundle] else io.in.asInstanceOf[DecoupledIO[EX_MEM_Bundle]].bits

    val memCmd  = inData.memCmd
    val memSize = inData.memSize
    val memSign = inData.memSign

    // 地址即上级的结果；待存的数据由原透传的 rs2 定夺
    val addr    = inData.aluOut
    val wdata   = inData.rs2Data

    // 从 MemSize 中的枚举解析我们需要访问的字节数目
    val memByteLen = MuxLookup(memSize, 4.U(8.W))(Seq(
      MemSize.B -> 1.U,
      MemSize.H -> 2.U,
      MemSize.W -> 4.U,
      MemSize.D -> 8.U
    ))

    // 1. 根据 LsuConfig 动态生成指定的访问端口和逻辑
    val rawRdata = WireInit(0.U(xlen.W))

    p.lsu.lsuMode match {
      case "dpi" =>
        // DPI 直通访存黑盒，直接利用 DPI-C 原生实现，无延迟
        val dpicLSU = Module(new DPIC_LSU(p.vaddrBits, xlen))
        dpicLSU.io.clk   := clock
        dpicLSU.io.en    := inValid && (memCmd === MemCmd.READ || memCmd === MemCmd.WRITE)
        dpicLSU.io.cmd   := memCmd === MemCmd.WRITE
        dpicLSU.io.addr  := addr
        dpicLSU.io.wdata := wdata
        dpicLSU.io.len   := memByteLen

        rawRdata := dpicLSU.io.rdata

      case "axi4" =>
        // TODO: 实现完整 AXI4 Burst 状态机交织访存
        rawRdata := 0.U

      case "cache" =>
        // TODO: 接管给 Data Cache 控制器并挂靠相关响应/失效机制
        rawRdata := 0.U

      case _ =>
        require(false, s"Unknown LSU mode: ${p.lsu.lsuMode}")
    }

    // 2. 读数据的偏移截尾处理
    val shiftAmount = MuxLookup(memSize, 0.U(6.W))(Seq(
      MemSize.B -> Cat(addr(1, 0), 0.U(3.W)).pad(6),
      MemSize.H -> Cat(addr(1), 0.U(4.W)).pad(6),
      MemSize.W -> (if (xlen == 64) Cat(addr(2), 0.U(5.W)).pad(6) else 0.U(6.W)),
      MemSize.D -> 0.U(6.W)
    ))
    val shiftedRdata = rawRdata >> shiftAmount

    // 3. 构建待写回的整数寄存器数据 rfData
    val rfData = WireInit(0.U(xlen.W))
    when(memCmd === MemCmd.READ) {
      if (xlen == 64) {
        rfData := MuxLookup(memSize, shiftedRdata)(Seq(
          MemSize.B -> Mux(memSign, Cat(Fill(56, shiftedRdata(7)), shiftedRdata(7, 0)), Cat(Fill(56, 0.U), shiftedRdata(7, 0))),
          MemSize.H -> Mux(memSign, Cat(Fill(48, shiftedRdata(15)), shiftedRdata(15, 0)), Cat(Fill(48, 0.U), shiftedRdata(15, 0))),
          MemSize.W -> Mux(memSign, Cat(Fill(32, shiftedRdata(31)), shiftedRdata(31, 0)), Cat(Fill(32, 0.U), shiftedRdata(31, 0))),
          MemSize.D -> shiftedRdata
        ))
      } else {
        rfData := MuxLookup(memSize, shiftedRdata)(Seq(
          MemSize.B -> Mux(memSign, Cat(Fill(24, shiftedRdata(7)), shiftedRdata(7, 0)), Cat(Fill(24, 0.U), shiftedRdata(7, 0))),
          MemSize.H -> Mux(memSign, Cat(Fill(16, shiftedRdata(15)), shiftedRdata(15, 0)), Cat(Fill(16, 0.U), shiftedRdata(15, 0))),
          MemSize.W -> shiftedRdata
        ))
      }
    } .otherwise {
      rfData := inData.aluOut
    }

    // 4. 重组前往 WB 的数据负载
    val msgOut = Wire(new MEM_WB_Bundle)
    msgOut          := DontCare
    msgOut.inst     := inData.inst
    msgOut.rfData   := rfData
    msgOut.pc       := inData.pc
    msgOut.rdaddr   := inData.rdaddr
    msgOut.wbTarget := inData.wbTarget
    msgOut.halt     := inData.halt
    msgOut.csrWdata := inData.csrWdata
    msgOut.csrAddr  := inData.csrAddr
    msgOut.csrOp    := inData.csrOp
    msgOut.memCmd   := inData.memCmd

    // 5. 连接输出级
    if (isSingleCycle) {
      io.out.asInstanceOf[MEM_WB_Bundle] := msgOut
    } else {
      val outDec = io.out.asInstanceOf[DecoupledIO[MEM_WB_Bundle]]
      val inDec  = io.in.asInstanceOf[DecoupledIO[EX_MEM_Bundle]]

      outDec.valid := inDec.valid
      outDec.bits  := msgOut
      inDec.ready  := outDec.ready
    }
  }
}
