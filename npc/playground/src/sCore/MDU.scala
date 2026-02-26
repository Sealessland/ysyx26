package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

class MDUIO(implicit p: CoreConfig) extends CoreBundle {
  val src1  = Input(UInt(xlen.W))
  val src2  = Input(UInt(xlen.W))
  val mduOp = Input(MduOp())
  val out   = Output(UInt(xlen.W))
}

class MDU()(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new MDUIO)

  if (fastMdu) {
    val in1 = io.src1
    val in2 = io.src2

    val isDivZero  = in2 === 0.U
    val isOverflow = (in1 === (1.U << (xlen - 1))) && (in2.andR) // in2 == -1

    val s1 = in1.asSInt
    val s2 = in2.asSInt

    // 考虑 64 位的乘法以便提取高 32 位 (对于 RV32)
    val extLen = xlen * 2
    val mulSig = (s1.pad(extLen) * s2.pad(extLen)).asUInt
    val mulHsu = (s1.pad(extLen) * in2.pad(extLen).asSInt).asUInt
    val mulUnS = (in1.pad(extLen) * in2.pad(extLen)).asUInt

    val mulh   = mulSig(extLen - 1, xlen)
    val mulhsu = mulHsu(extLen - 1, xlen)
    val mulhu  = mulUnS(extLen - 1, xlen)

    val divOut  = Mux(isDivZero, ~(0.U(xlen.W)), Mux(isOverflow, in1, (s1 / s2).asUInt))
    val divuOut = Mux(isDivZero, ~(0.U(xlen.W)), in1 / in2)
    val remOut  = Mux(isDivZero, in1, Mux(isOverflow, 0.U(xlen.W), (s1 % s2).asUInt))
    val remuOut = Mux(isDivZero, in1, in1 % in2)

    io.out := MuxLookup(io.mduOp, 0.U(xlen.W))(Seq(
      MduOp.MUL    -> (in1 * in2),
      MduOp.MULH   -> mulh,
      MduOp.MULHSU -> mulhsu,
      MduOp.MULHU  -> mulhu,
      MduOp.DIV    -> divOut,
      MduOp.DIVU   -> divuOut,
      MduOp.REM    -> remOut,
      MduOp.REMU   -> remuOut
    ))
  } else {
    // 带有状态机的迭代乘除法单元架构，暂时留空占位
    // 用户要求：确保普通版本能完成流程后再设计
    val iterativeMdu = Module(new IterativeMDU())
    iterativeMdu.io.src1  := io.src1
    iterativeMdu.io.src2  := io.src2
    iterativeMdu.io.mduOp := io.mduOp
    io.out := iterativeMdu.io.out
  }
}

class IterativeMDU()(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new MDUIO)
  // TODO: Implement state machine for iterative multiplication and division
  // Current behavior is bypass with 0 to allow chisel elaboration.
  io.out := 0.U
}
