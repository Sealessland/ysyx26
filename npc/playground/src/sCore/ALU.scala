package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

// -----------------------------------------------------------------------------
// 1. 定义 ALU 的接口 (Bundle)
// -----------------------------------------------------------------------------
class ALUIO(implicit p: CoreConfig) extends CoreBundle {
  val src1   = Input(UInt(xlen.W))
  val src2   = Input(UInt(xlen.W))
  val aluOp  = Input(AluOp())
  
  // 供未来的 DecodeRules 扩展 (例如在 RV64 环境下识别类似 addw/sllw 这类 isWord 的指令)
  val isWord = Input(Bool())
  val out    = Output(UInt(xlen.W))
}

// -----------------------------------------------------------------------------
// 2. ALU 核心逻辑模块
// -----------------------------------------------------------------------------
class ALU(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new ALUIO)

  val in1 = io.src1
  val in2 = io.src2

  // 计算移位量
  // RV64下根据 isWord 选择低 5 还是低 6 位作为 shift amount
  // RV32下总是选择低 5 位
  val shamt = if (xlen == 64) {
    Mux(io.isWord, in2(4, 0), in2(5, 0))
  } else {
    in2(4, 0)
  }

  // --------------------------------------------------------
  // 辅助函数：针对 RV64 的字号（Word）指令做 32位有符号扩展
  // 如果是 RV32，则会在综合时通过条件判断优化掉
  // --------------------------------------------------------
  def signExt32(res: UInt): UInt = {
    if (xlen == 64) {
      val res32 = res(31, 0)
      Cat(Fill(32, res32(31)), res32)
    } else {
      res
    }
  }

  // --------------------------------------------------------
  // 计算每种基本操作的数据并行结果
  // --------------------------------------------------------
  val addOut  = in1 + in2
  val subOut  = in1 - in2
  val andOut  = in1 & in2
  val orOut   = in1 | in2
  val xorOut  = in1 ^ in2
  
  // 移位超出指定位数通过切片保障固定位宽防止宽度不匹配
  val sllOut  = (in1 << shamt)(xlen - 1, 0)
  val srlOut  = in1 >> shamt
  val sraOut  = (in1.asSInt >> shamt).asUInt
  
  val sltOut  = (in1.asSInt < in2.asSInt).asUInt
  val sltuOut = (in1 < in2).asUInt

  // 对RV64的字长特殊指令 (srlw, sraw) 进行提前裁切操作
  val srlwOut = if (xlen == 64) signExt32(in1(31, 0) >> shamt) else srlOut
  val srawOut = if (xlen == 64) signExt32((in1(31, 0).asSInt >> shamt).asUInt) else sraOut

  // --------------------------------------------------------
  // 多路选择最后输出
  // --------------------------------------------------------
  io.out := MuxLookup(io.aluOp, 0.U(xlen.W))(Seq(
    AluOp.ADD  -> Mux(io.isWord, signExt32(addOut), addOut),
    AluOp.SUB  -> Mux(io.isWord, signExt32(subOut), subOut),
    AluOp.AND  -> andOut,
    AluOp.OR   -> orOut,
    AluOp.XOR  -> xorOut,
    AluOp.SLL  -> Mux(io.isWord, signExt32(sllOut), sllOut),
    AluOp.SRL  -> Mux(io.isWord, srlwOut, srlOut),
    AluOp.SRA  -> Mux(io.isWord, srawOut, sraOut),
    AluOp.SLT  -> sltOut,
    AluOp.SLTU -> sltuOut,
    AluOp.CPY  -> in1
  ))
}
