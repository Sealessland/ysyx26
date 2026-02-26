package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

// -----------------------------------------------------------------------------
// WBU (写回单元) IO 定义
// -----------------------------------------------------------------------------
class WBUIO(implicit p: CoreConfig) extends CoreBundle {
  val in  = Flipped(if (isSingleCycle) new MEM_WB_Bundle else Decoupled(new MEM_WB_Bundle))
  
  // WB 的最后阶段需要给出暴露在外的测试引脚：当前提交的这一条操作的结果状态
  val wb_pc        = Output(UInt(vaddrBits.W))
  val wb_valid     = Output(Bool())    // 表明是否在此刻有效提交
  val wb_inst      = Output(UInt(32.W))
  val wb_is_store  = Output(Bool())
  val wb_halt      = Output(Bool())
  
  // 异常处理与 CSR 状态维护的专用输出
  val wb_exception = Output(Bool())
  val wb_epc       = Output(UInt(vaddrBits.W))
  val wb_cause     = Output(UInt(xlen.W))
  
  val rf_waddr = Output(UInt(5.W))
  val rf_wdata = Output(UInt(xlen.W))
  val rf_wen   = Output(Bool())
  
  // CSR 写接口
  val csr_waddr = Output(UInt(12.W))
  val csr_wdata = Output(UInt(xlen.W))
  val csr_wen   = Output(Bool())
  val csr_op    = Output(CsrOp())
}

// -----------------------------------------------------------------------------
// 写回单元 (Write Back Unit)
// -----------------------------------------------------------------------------
class WBU()(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new WBUIO)
  
  // 解包握手或者单周期真值
  val inValid = if (isSingleCycle) true.B else io.in.asInstanceOf[DecoupledIO[MEM_WB_Bundle]].valid
  val inData  = if (isSingleCycle) io.in.asInstanceOf[MEM_WB_Bundle] else io.in.asInstanceOf[DecoupledIO[MEM_WB_Bundle]].bits

  // 对外暴露当前的 PC 以供比对测试和跟踪 (Commit Log)
  io.wb_pc        := inData.pc
  io.wb_valid     := inValid
  io.wb_inst      := inData.inst
  io.wb_is_store  := (inData.memCmd === MemCmd.WRITE)
  io.wb_halt      := inData.halt
  
  // 决定最终要写什么进通用寄存器
  // CSR 指令同时也需要向通用整数寄存器中写入旧的 CSR 值
  // RISC-V 规范：x0 寄存器硬连线为 0，不能写入任何值，因此强行抑制 rdaddr == 0 的写使能
  val enableIntRegWrite = inValid && (inData.rdaddr =/= 0.U(5.W)) && 
                          (inData.wbTarget === WbTarget.INT_REG || inData.wbTarget === WbTarget.CSR_REG) 

  io.rf_waddr := inData.rdaddr
  io.rf_wdata := inData.rfData
  io.rf_wen   := enableIntRegWrite
  
  val enableCsrWrite = inValid && (inData.wbTarget === WbTarget.CSR_REG)
  io.csr_waddr := inData.csrAddr
  io.csr_wdata := inData.csrWdata
  io.csr_wen   := enableCsrWrite
  io.csr_op    := inData.csrOp
  
  // Ebreak 停机处理 DPI-C 接口
  val dpicEbreak = Module(new DPIC_Ebreak())
  dpicEbreak.io.clk := clock
  dpicEbreak.io.en  := inValid && inData.halt

  // 抛出异常信号给到外部 CSRFile
  // ecall 指令特征：它是 SYS 系统的例外指令 (在我们的解码矩阵中，ecall 的 imm被赋作了类似I-type, inst形如 h00000073)
  val isEcall = inData.inst === "h00000073".U
  io.wb_exception := inValid && isEcall
  io.wb_epc       := inData.pc
  io.wb_cause     := 0xb.U // Machine call cause

  // 调试输出
  when(inData.halt) {
    printf(p"[WBU] halt signal detected! inValid=$inValid, pc=0x${Hexadecimal(inData.pc)}\n")
  }
  
  // 若流水线解耦模式下，WBU 位于最末端，永远接收
  if (!isSingleCycle) {
    io.in.asInstanceOf[DecoupledIO[MEM_WB_Bundle]].ready := true.B
  }
}
