package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

class BRUIO(implicit p: CoreConfig) extends CoreBundle {
  val rs1_data = Input(UInt(xlen.W))
  val rs2_data = Input(UInt(xlen.W))
  val pc       = Input(UInt(vaddrBits.W))
  val imm      = Input(UInt(xlen.W))
  val bruOp    = Input(BruOp())
  
  // 分支预测扩展接口 (预留，用于未来检测预测是否失败)
  val bpd_predict_taken = Input(Bool())
  val bpd_predict_target = Input(UInt(vaddrBits.W))

  // 向 IFU/PC 控制侧发送的修正/重定向指令
  val redirect_valid  = Output(Bool())
  val redirect_target = Output(UInt(vaddrBits.W))
}

class BRU()(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new BRUIO)

  val in1 = io.rs1_data
  val in2 = io.rs2_data

  val eq   = in1 === in2
  val neq  = in1 =/= in2
  val lt   = in1.asSInt < in2.asSInt
  val ge   = in1.asSInt >= in2.asSInt
  val ltu  = in1 < in2
  val geu  = in1 >= in2

  val isJump = WireInit(false.B)
  val jumpTarget = WireInit(0.U(vaddrBits.W))

  switch(io.bruOp) {
    is(BruOp.BEQ) {
      isJump := eq
      jumpTarget := io.pc + io.imm
    }
    is(BruOp.BNE) {
      isJump := neq
      jumpTarget := io.pc + io.imm
    }
    is(BruOp.BLT) {
      isJump := lt
      jumpTarget := io.pc + io.imm
    }
    is(BruOp.BGE) {
      isJump := ge
      jumpTarget := io.pc + io.imm
    }
    is(BruOp.BLTU) {
      isJump := ltu
      jumpTarget := io.pc + io.imm
    }
    is(BruOp.BGEU) {
      isJump := geu
      jumpTarget := io.pc + io.imm
    }
    is(BruOp.JAL) {
      isJump := true.B
      jumpTarget := io.pc + io.imm
    }
    is(BruOp.JALR) {
      isJump := true.B
      // JALR 把低位置 0
      jumpTarget := (in1 + io.imm) & (~1.U(xlen.W))
    }
    is(BruOp.ECALL) {
      isJump := true.B
      jumpTarget := in1 // ECALL 时由于配置 rs1 为 csr_val(MTVEC)，此处直接跳
    }
    is(BruOp.MRET) {
      isJump := true.B
      jumpTarget := in1 // MRET 时由于配置 rs1 为 csr_val(MEPC)，此处直接跳
    }
  }

  // 目前是不带预测的 Base 版本：判断是否需要重定向直接根据 isJump 输出
  // 在以后结合 bpd_predict，这里将会变为判定 (实际跳转状态 =/= 预期跳转状态) 时才触发 valid
  io.redirect_valid  := isJump
  io.redirect_target := jumpTarget
}
