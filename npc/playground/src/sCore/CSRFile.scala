package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

// -----------------------------------------------------------------------------
// 系统控制与状态寄存器堆 (CSR File)
// -----------------------------------------------------------------------------
class CSRFile(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new CSRFileIO)
  
  // CSR 地址常量
  val MSTATUS = 0x300.U(12.W)
  val MTVEC   = 0x305.U(12.W)
  val MEPC    = 0x341.U(12.W)
  val MCAUSE  = 0x342.U(12.W)

  // CSR 寄存器实例化
  val mstatus = RegInit(0.U(xlen.W))
  val mtvec   = RegInit(0.U(xlen.W))
  val mepc    = RegInit(0.U(xlen.W))
  val mcause  = RegInit(0.U(xlen.W))

  // 1. 读逻辑
  io.csr_rdata := MuxLookup(io.csr_raddr, 0.U(xlen.W))(Seq(
    MSTATUS -> mstatus,
    MTVEC   -> mtvec,
    MEPC    -> mepc,
    MCAUSE  -> mcause
  ))

  // 2. 写反馈逻辑
  when(io.exception) {
    // 处理 ecall 或 ebreak 等异常，这里仅作接口展示
    mepc   := io.epc
    mcause := io.cause
  }.elsewhen(io.csr_wen) {
    val old_val = MuxLookup(io.csr_waddr, 0.U(xlen.W))(Seq(
      MSTATUS -> mstatus,
      MTVEC   -> mtvec,
      MEPC    -> mepc,
      MCAUSE  -> mcause
    ))
    val new_val = WireInit(old_val)
    
    // 基于操作码的位控制逻辑
    switch(io.csr_op) {
      is(CsrOp.RW) { new_val := io.csr_wdata }
      is(CsrOp.RS) { new_val := old_val | io.csr_wdata } // Bit Set
      is(CsrOp.RC) { new_val := old_val & ~io.csr_wdata } // Bit Clear
    }
    
    // 根据写地址实际更新寄存器
    when(io.csr_waddr === MSTATUS) { mstatus := new_val }
    when(io.csr_waddr === MTVEC)   { mtvec   := new_val }
    when(io.csr_waddr === MEPC)    { mepc    := new_val }
    when(io.csr_waddr === MCAUSE)  { mcause  := new_val }
  }
}
