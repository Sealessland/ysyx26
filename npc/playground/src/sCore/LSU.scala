package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

// -----------------------------------------------------------------------------
// 传递给写回级 (WB) 的负载信息
// -----------------------------------------------------------------------------
class MEM_WB_Bundle(implicit p: CoreConfig) extends CoreBundle {
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
}

// -----------------------------------------------------------------------------
// LSU 的 IO 接口
// -----------------------------------------------------------------------------
class LSUIO(implicit p: CoreConfig) extends CoreBundle {
  val in  = Flipped(if (isSingleCycle) new EX_MEM_Bundle else Decoupled(new EX_MEM_Bundle))
  val out = if (isSingleCycle) Output(new MEM_WB_Bundle) else Decoupled(new MEM_WB_Bundle)
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

    case "axiLite" =>
      // TODO: 实现 AXI4-Lite 单拍突发握手访存
      rawRdata := 0.U
      
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
  // 根据访存类型动态遮掩无关对齐位。例如 Word 访存以 4 字节为单位，低两位舍去而 addr(2) 是有效的（若xlen为64），因此用 4.U 倍数去卡。
  // RV32 下 lw 的 addr(1,0) 是 0，偏移量应为 0。使用显式拼接避免位宽扩展误用更高位地址:
  val shiftAmount = MuxLookup(memSize, 0.U(6.W))(Seq(
    MemSize.B -> Cat(addr(1, 0), 0.U(3.W)).pad(6),
    MemSize.H -> Cat(addr(1), 0.U(4.W)).pad(6),
    MemSize.W -> (if (xlen == 64) Cat(addr(2), 0.U(5.W)).pad(6) else 0.U(6.W)),
    MemSize.D -> 0.U(6.W)
  ))
  val shiftedRdata = rawRdata >> shiftAmount

  // 3. 构建待写回的整数寄存器数据 rfData
  val rfData = WireInit(0.U(xlen.W))
  
  // 只在需要从存储器读（Load）时进行符号或无符号扩展；否则原样下发 ALU 的计算结果！这点非常关键，决定了是算术结果还是访存结果被写回
  when(memCmd === MemCmd.READ) {
    if (xlen == 64) {
      rfData := MuxLookup(memSize, shiftedRdata)(Seq(
        MemSize.B -> Mux(memSign, Cat(Fill(56, shiftedRdata(7)), shiftedRdata(7, 0)), Cat(Fill(56, 0.U), shiftedRdata(7, 0))),
        MemSize.H -> Mux(memSign, Cat(Fill(48, shiftedRdata(15)), shiftedRdata(15, 0)), Cat(Fill(48, 0.U), shiftedRdata(15, 0))),
        MemSize.W -> Mux(memSign, Cat(Fill(32, shiftedRdata(31)), shiftedRdata(31, 0)), Cat(Fill(32, 0.U), shiftedRdata(31, 0))),
        MemSize.D -> shiftedRdata
      ))
    } else { // 32-bit System
      rfData := MuxLookup(memSize, shiftedRdata)(Seq(
        MemSize.B -> Mux(memSign, Cat(Fill(24, shiftedRdata(7)), shiftedRdata(7, 0)), Cat(Fill(24, 0.U), shiftedRdata(7, 0))),
        MemSize.H -> Mux(memSign, Cat(Fill(16, shiftedRdata(15)), shiftedRdata(15, 0)), Cat(Fill(16, 0.U), shiftedRdata(15, 0))),
        MemSize.W -> shiftedRdata
      ))
    }
  }.otherwise {
    rfData := inData.aluOut
  }

  // 4. 重组前往 WB 的数据负载
  val msgOut = Wire(new MEM_WB_Bundle)
  msgOut          := DontCare
  msgOut.rfData   := rfData
  msgOut.pc       := inData.pc
  msgOut.rdaddr   := inData.rdaddr
  msgOut.wbTarget := inData.wbTarget
  msgOut.halt     := inData.halt

  msgOut.csrWdata := inData.csrWdata
  msgOut.csrAddr  := inData.csrAddr
  msgOut.csrOp    := inData.csrOp

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
