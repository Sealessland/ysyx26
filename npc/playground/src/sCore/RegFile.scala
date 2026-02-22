package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

// -----------------------------------------------------------------------------
// 通用寄存器堆读写接口
// -----------------------------------------------------------------------------
class RegFileIO(implicit p: CoreConfig) extends CoreBundle {
  // 读端口
  val rs1_addr = Input(UInt(5.W))
  val rs1_data = Output(UInt(xlen.W))
  
  val rs2_addr = Input(UInt(5.W))
  val rs2_data = Output(UInt(xlen.W))

  // 写回端口
  val rd_addr  = Input(UInt(5.W))
  val rd_data  = Input(UInt(xlen.W))
  val rd_wen   = Input(Bool())
}

// -----------------------------------------------------------------------------
// 留给未来的 CSR 扩展接口 (Stub)
// 与通用 RegFile 完全解耦，保持结构正交
// -----------------------------------------------------------------------------
class CSRFileIO(implicit p: CoreConfig) extends CoreBundle {
  // CSR 读端口
  val csr_raddr = Input(UInt(12.W))
  val csr_rdata = Output(UInt(xlen.W))
  
  // CSR 写端口
  val csr_waddr = Input(UInt(12.W))
  val csr_wdata = Input(UInt(xlen.W))
  val csr_wen   = Input(Bool())
  val csr_op    = Input(CsrOp()) // 透传具体的 CSR 操作码 (RW, RS, RC 等)
  
  // 异常/特权转移相关的系统寄存器接口 (后续可根据特权级架构扩展)
  val exception = Input(Bool())
  val epc       = Input(UInt(vaddrBits.W))
  val cause     = Input(UInt(xlen.W))
}

// -----------------------------------------------------------------------------
// 通用整数寄存器堆 (Integer Register File)
// -----------------------------------------------------------------------------
class RegFile(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new RegFileIO)

  // 实例化 32 个 xlen 宽度的寄存器
  // Chisel 中的 SyncReadMem 适合 SRAM，但 RegFile 通常不需要同步读，
  // 因此使用 Reg 代替，或者基于 Mem 构建的组合逻辑读。对于 FPGA 综合，这里使用组合读的 Mem 或 RegVec。
  val regs = Mem(32, UInt(xlen.W))

  // 1. 读逻辑：硬连线 x0 为 0
  io.rs1_data := Mux(io.rs1_addr === 0.U, 0.U(xlen.W), regs(io.rs1_addr))
  io.rs2_data := Mux(io.rs2_addr === 0.U, 0.U(xlen.W), regs(io.rs2_addr))

  // 2. 写反馈逻辑：禁止对 x0 写操作
  // 带有优先级的写后直通读 (Bypass/Forwarding) 可以在此处做，也可以由前递网络 (Forwarding Unit) 负责。
  // 鉴于模块化要求，这里只处理基础存储。
  when(io.rd_wen && io.rd_addr =/= 0.U) {
    regs(io.rd_addr) := io.rd_data
  }
}
