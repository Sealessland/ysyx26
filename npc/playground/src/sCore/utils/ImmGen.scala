package sCore.utils

import chisel3._
import chisel3.util._

// -----------------------------------------------------------------------------
// 独立的立即数生成器：专注于位拼接
// -----------------------------------------------------------------------------
object ImmGen {
  def apply(inst: UInt, immType: ImmTypeEnum.Type, xlen: Int): UInt = {
    // 采用 .asSInt.pad(xlen).asUInt 彻底消灭硬编码扩展造成的位宽溢出/错误问题
    val imm_i      = inst(31, 20).asSInt.pad(xlen).asUInt
    val imm_s      = Cat(inst(31, 25), inst(11, 7)).asSInt.pad(xlen).asUInt
    val imm_b      = Cat(inst(31), inst(7), inst(30, 25), inst(11, 8), 0.U(1.W)).asSInt.pad(xlen).asUInt
    val imm_u      = Cat(inst(31, 12), 0.U(12.W)).asSInt.pad(xlen).asUInt
    val imm_j      = Cat(inst(31), inst(19, 12), inst(20), inst(30, 21), 0.U(1.W)).asSInt.pad(xlen).asUInt
    
    // shamt 是无符号数，pad 会自动做前面填 0 的扩展
    val imm_shamtd = inst(25, 20).pad(xlen) 
    val imm_shamtw = inst(24, 20).pad(xlen)
    val imm_z      = inst(19, 15).pad(xlen)

    MuxLookup(immType, 0.U)(Seq(
      ImmTypeEnum.immI      -> imm_i,
      ImmTypeEnum.immS      -> imm_s,
      ImmTypeEnum.immB      -> imm_b,
      ImmTypeEnum.immU      -> imm_u,
      ImmTypeEnum.immJ      -> imm_j,
      ImmTypeEnum.immShamtD -> imm_shamtd,
      ImmTypeEnum.immShamtW -> imm_shamtw,
      ImmTypeEnum.immZ      -> imm_z
    ))
  }
}
