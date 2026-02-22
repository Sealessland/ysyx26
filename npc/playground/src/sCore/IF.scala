package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

class RedirectIO(implicit p: CoreConfig) extends CoreBundle {
  val valid  = Output(Bool())       // 是否发生跳转重定向
  val target = Output(UInt(vaddrBits.W)) // 重定向的绝对目标地址
}

class IF_ID_Bundle(implicit p: CoreConfig) extends CoreBundle {
  val pc   = UInt(vaddrBits.W)
  val inst = UInt(32.W)
}

class IF()(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new CoreBundle {
    // single cycle
    val sc_inst = if (isSingleCycle) Some(Output(UInt(32.W))) else None
    val sc_pc   = if (isSingleCycle) Some(Output(UInt(vaddrBits.W))) else None
    
    // pipe line
    val nextStage = if (!isSingleCycle) Some(Decoupled(new IF_ID_Bundle)) else None
    
    val redirectEX = Flipped(new RedirectIO) // 来自 EX 阶段的分支跳转
    val redirectWB = Flipped(new RedirectIO) // 来自 WB/CSR 的异常中断跳转
  })

  val pcReg = RegInit("h80000000".U(vaddrBits.W)) 

  // -----------------------------------------------------------------
  // 解耦的取指发报机：IFU 完全不关心自己外接的是 DPI、SRAM 还是 AXI
  // -----------------------------------------------------------------
  val fetchUnit = Module(new FetchUnit())
  
  fetchUnit.io.mem.req.valid := true.B
  fetchUnit.io.mem.req.bits.addr := pcReg
  fetchUnit.io.mem.resp.ready := true.B // 处理悬空：对于单周期或者无等待的取指直接拉高ready
  
  // 从取指单元拿回来的数据，DPI 模式下因为 valid 常为 true，直接可用
  val fetchedInst = fetchUnit.io.mem.resp.bits.data
  val outValid = fetchUnit.io.mem.resp.valid
  val pcNext = WireDefault(pcReg + instBytes.U) 

  when(io.redirectWB.valid) {
    pcNext := io.redirectWB.target
  } .elsewhen(io.redirectEX.valid) {
    pcNext := io.redirectEX.target
  }

  // 1. 根据当前模式控制 PC 更新
  if (isSingleCycle) {
    // 单周期：每个时钟直接更新 PC
    pcReg := pcNext
    
    io.sc_pc.get := pcReg
    io.sc_inst.get := fetchedInst
  } else {
    // 流水线设计：与流水级握手 (例如握手成功或者发生 flush 才移动 PC)
    val outReady = io.nextStage.get.ready

    io.nextStage.get.valid := outValid
    io.nextStage.get.bits.pc := pcReg
    io.nextStage.get.bits.inst := fetchedInst
    
    // 只有当下一级准备好接收，或者被强行重定向时，才能改变 PC
    when(io.redirectEX.valid || io.redirectWB.valid || (outValid && outReady)) {
      pcReg := pcNext
    }
  }
}

