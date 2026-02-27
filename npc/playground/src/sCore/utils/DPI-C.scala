package sCore.utils

import chisel3._
import chisel3.util._

/**
 * 通用的取指总线接口规范 (Decoupled握手)
 * 无论是 DPI / AXI4-Lite / Cache，全部向外暴露此一致的接口
 */
class MemReadIO(val addrBits: Int, val dataBits: Int) extends Bundle {
  val req = Decoupled(new Bundle {
    val addr = UInt(addrBits.W)
  })
  val resp = Flipped(Decoupled(new Bundle {
    val data = UInt(dataBits.W)
  }))
}

// 供 IF 调用的统一模块 (Generator Pattern 核心)
class FetchUnit()(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new Bundle {
    val mem = Flipped(new MemReadIO(p.paddrBits, 32)) 
    val axi = if (p.frontend.fetchMode == "axiLite") Some(new AxiLiteMasterIO(p.paddrBits, p.xlen)) else None
  })

  // 高扩展性路由：根据配置项，动态生成真正综合到底层的硬件！
  // 这些 case 分支在电路生成时(elaboration)会直接裁剪掉不需要的代码
  p.frontend.fetchMode match {
    case "dpi" =>
      // 1. DPI 直取模式：纯组合逻辑，直接丢弃延时
      val dpic = Module(new DPIC_Fetch(p.paddrBits))
      
      io.mem.req.ready := true.B
      dpic.io.raddr := io.mem.req.bits.addr
      
      io.mem.resp.valid := true.B
      io.mem.resp.bits.data := dpic.io.rdata

    case "sramLite" =>
      // 2. TODO: 结合 AXI4-Lite 的有限状态机读写
      io.mem.req.ready := false.B
      io.mem.resp.valid := false.B
      io.mem.resp.bits.data := 0.U

    case "sram" =>
      // 3. TODO: 结合完整的 AXI4 Burst 读写
      io.mem.req.ready := false.B
      io.mem.resp.valid := false.B
      io.mem.resp.bits.data := 0.U

    case "cache" =>
      // 4. TODO: 连接 I-Cache 模块
      io.mem.req.ready := false.B
      io.mem.resp.valid := false.B
      io.mem.resp.bits.data := 0.U
      
    case "axiLite" =>
      // 5. AXI4-Lite 取指（单 in-flight）
      val axi = io.axi.get
      val busBytes = (p.xlen / 8)
      val byteOffBits = log2Ceil(busBytes)
      val addrAlignMask = Cat(Fill(p.paddrBits - byteOffBits, 1.U), 0.U(byteOffBits.W))

      val sIdle :: sAddr :: sWait :: sResp :: Nil = Enum(4)
      val state = RegInit(sIdle)
      val addrReg = Reg(UInt(p.paddrBits.W))
      val instReg = Reg(UInt(32.W))
      val respValid = RegInit(false.B)

      io.mem.req.ready := (state === sIdle) && !respValid
      when(io.mem.req.fire) {
        addrReg := io.mem.req.bits.addr
        state := sAddr
      }

      axi.aw.valid := false.B
      axi.w.valid  := false.B
      axi.b.ready  := false.B
      axi.aw.bits.addr := 0.U
      axi.aw.bits.prot := 0.U
      axi.w.bits.data  := 0.U
      axi.w.bits.strb  := 0.U

      axi.ar.valid := (state === sAddr)
      axi.ar.bits.addr := addrReg & addrAlignMask
      axi.ar.bits.prot := 0.U

      axi.r.ready := (state === sWait)
      when(state === sAddr && axi.ar.fire) {
        state := sWait
      }
      when(state === sWait && axi.r.fire) {
        val shift = (addrReg(byteOffBits - 1, 0) << 3).asUInt
        instReg := (axi.r.bits.data >> shift)(31, 0)
        respValid := true.B
        state := sResp
      }

      io.mem.resp.valid := respValid
      io.mem.resp.bits.data := instReg
      when(io.mem.resp.fire) {
        respValid := false.B
        state := sIdle
      }

    case _ =>
      require(false, s"Unknown fetch mode: ${p.frontend.fetchMode}. Must be one of: dpi, sramLite, sram, cache, axiLite")
  }
}

// -------------------------------------------------------------
// DPI-C 黑盒定义 - 使用 Chisel 7.x 官方最高效的 HasExtModuleInline
// -------------------------------------------------------------
class DPIC_Fetch(addrBits: Int) extends ExtModule {
  val io = IO(new Bundle {
    val raddr = Input(UInt(addrBits.W))
    val rdata = Output(UInt(32.W))
  })
  
  // 保持生成的 SystemVerilog module 名字与类名一致
  override val desiredName = "DPIC_Fetch"

  // Chisel 7.5+ 官方推荐特性：ExtModule 原生内置了加载外部 Verilog 文件的功能。
  // 通过 addPath() 可以安全地导入存放在项目中其他地方的代码，而不再需要 HasBlackBoxResource / HasExtModuleInline
  addPath("playground/src/sCore/utils/vsrc/DPIC_Fetch.sv")
}

// -------------------------------------------------------------
// DPI-C Ebreak Blackbox
// -------------------------------------------------------------
class DPIC_Ebreak extends ExtModule {
  val io = IO(new Bundle {
    val clk = Input(Clock())
    val en  = Input(Bool())
  })
  
  override val desiredName = "DPIC_Ebreak"
  addPath("playground/src/sCore/utils/vsrc/DPIC_Ebreak.sv")
}
