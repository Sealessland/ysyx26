package sCore.utils

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._
import org.chipsalliance.rvdecoderdb

//======================================================================
// 全局解码相关枚举定义 (正交多维架构)
//======================================================================
object FUType extends ChiselEnum { val ALU, BRU, LSU, MDU, CSR, FPU, NONE = Value }
object Src1Sel extends ChiselEnum { val RS1, PC, ZERO, UIMM, CSR_VAL = Value }
object Src2Sel extends ChiselEnum { val RS2, IMM, FOUR = Value }
object AluOp extends ChiselEnum { val ADD, SUB, AND, OR, XOR, SLL, SRL, SRA, SLT, SLTU, CPY = Value }
object BruOp extends ChiselEnum { val NONE, BEQ, BNE, BLT, BGE, BLTU, BGEU, JAL, JALR, ECALL, MRET = Value }
object CsrOp extends ChiselEnum { val NONE, RW, RS, RC, SYS, ECALL, MRET = Value }
object MduOp extends ChiselEnum { val NONE, MUL, MULH, MULHSU, MULHU, DIV, DIVU, REM, REMU = Value }
object MemCmd extends ChiselEnum { val NONE, READ, WRITE, AMO = Value }
object MemSize extends ChiselEnum { val B, H, W, D = Value }
object WbTarget extends ChiselEnum { val NONE, INT_REG, FP_REG, CSR_REG = Value }
object ImmTypeEnum extends ChiselEnum { val immNone, immI, immS, immB, immU, immJ, immShamtD, immShamtW, immZ = Value }

//======================================================================
// 指令包装器与规则对象工厂
//======================================================================
case class Insn(inst: rvdecoderdb.Instruction) extends DecodePattern {
  override def bitPat: BitPat = BitPat("b" + inst.encoding.toString().replace("-", "?"))
}

object DecodeRules {
  
  def boolField(nameStr: String)(cond: rvdecoderdb.Instruction => Boolean): BoolDecodeField[Insn] = 
    new BoolDecodeField[Insn] {
      override def name: String = nameStr
      override def genTable(i: Insn): BitPat = if (cond(i.inst)) y else n
    }

  def enumField[T <: ChiselEnum](nameStr: String, enumType: T)(mapFunc: rvdecoderdb.Instruction => T#Type): DecodeField[Insn, T#Type] =
    new DecodeField[Insn, T#Type] {
      override def name: String = nameStr
      override def chiselType: T#Type = enumType()
      override def genTable(i: Insn): BitPat = {
        val tpe = mapFunc(i.inst)
        BitPat(tpe.litValue.U(enumType.getWidth.W))
      }
    }

  // ==========================================
  // 【五维解码矩阵】 - 数据驱动体系核心
  // ==========================================

  // [维度一：派遣路由 (Dispatch / FU Type)]
  val FuTypeExp = enumField("fuType", FUType) { i =>
    i.name match {
      case "lb" | "lh" | "lw" | "ld" | "lbu" | "lhu" | "lwu" | "sb" | "sh" | "sw" | "sd" | "lr.w" | "sc.w" | "lr.d" | "sc.d" => FUType.LSU
      case "beq" | "bne" | "blt" | "bge" | "bltu" | "bgeu" | "jal" | "jalr" => FUType.BRU
      case "csrrw" | "csrrs" | "csrrc" | "csrrwi" | "csrrsi" | "csrrci" | "ecall" | "ebreak" | "mret" | "sret" | "wfi" => FUType.CSR
      case "mul" | "mulh" | "mulhsu" | "mulhu" | "div" | "divu" | "rem" | "remu" | "mulw" | "divw" | "divuw" | "remw" | "remuw" => FUType.MDU
      case "add" | "sub" | "sll" | "slt" | "sltu" | "xor" | "srl" | "sra" | "or" | "and" |
           "addi" | "slti" | "sltiu" | "xori" | "ori" | "andi" | "slli" | "srli" | "srai" |
           "addw" | "subw" | "sllw" | "srlw" | "sraw" | "addiw" | "slliw" | "srliw" | "sraiw" |
           "lui" | "auipc" => FUType.ALU
      case _ => FUType.NONE
    }
  }

  // [维度二：操作数网络 (Operand Routing)]
  val Src1Exp = enumField("src1Sel", Src1Sel) { i =>
    i.name match {
      case "auipc" | "jal" | "jalr" => Src1Sel.PC
      case "lui" => Src1Sel.ZERO
      case "csrrwi" | "csrrsi" | "csrrci" => Src1Sel.UIMM
      case "ecall" | "mret" => Src1Sel.CSR_VAL
      case _ => Src1Sel.RS1
    }
  }

  val Src2Exp = enumField("src2Sel", Src2Sel) { i =>
    i.name match {
      case "jal" | "jalr" => Src2Sel.FOUR
      case "addi" | "slti" | "sltiu" | "xori" | "ori" | "andi" | "slli" | "srli" | "srai" |
           "addiw" | "slliw" | "srliw" | "sraiw" | "lui" | "auipc" |
           "lb" | "lh" | "lw" | "ld" | "lbu" | "lhu" | "lwu" | "sb" | "sh" | "sw" | "sd" => Src2Sel.IMM
      case _ => Src2Sel.RS2
    }
  }

  // [维度三：微操作码 (Micro-Opcode)]
  val AluOpExp = enumField("aluOp", AluOp) { i =>
    i.name match {
      case "sub" | "subw" => AluOp.SUB
      case "and" | "andi" => AluOp.AND
      case "or" | "ori" => AluOp.OR
      case "xor" | "xori" => AluOp.XOR
      case "sll" | "slli" | "sllw" | "slliw" => AluOp.SLL
      case "srl" | "srli" | "srlw" | "srliw" => AluOp.SRL
      case "sra" | "srai" | "sraw" | "sraiw" => AluOp.SRA
      case "slt" | "slti" => AluOp.SLT
      case "sltu" | "sltiu" => AluOp.SLTU
      case _ => AluOp.ADD // Default covering ADD, ADDI, LUI, AUIPC, LOADS, STORES, JAL, JALR
    }
  }

  val BruOpExp = enumField("bruOp", BruOp) { i =>
    i.name match {
      case "beq"  => BruOp.BEQ
      case "bne"  => BruOp.BNE
      case "blt"  => BruOp.BLT
      case "bge"  => BruOp.BGE
      case "bltu" => BruOp.BLTU
      case "bgeu" => BruOp.BGEU
      case "jal"  => BruOp.JAL
      case "jalr" => BruOp.JALR
      case "ecall" => BruOp.ECALL
      case "mret"  => BruOp.MRET
      case _ => BruOp.NONE
    }
  }

  val CsrOpExp = enumField("csrOp", CsrOp) { i =>
    i.name match {
      case "csrrw" | "csrrwi" => CsrOp.RW
      case "csrrs" | "csrrsi" => CsrOp.RS
      case "csrrc" | "csrrci" => CsrOp.RC
      case "ecall" => CsrOp.ECALL
      case "mret"  => CsrOp.MRET
      case "ebreak" | "sret" | "wfi" => CsrOp.SYS
      case _ => CsrOp.NONE
    }
  }

  // [维度四：访存控制 (Memory Control)]
  val MemCmdExp = enumField("memCmd", MemCmd) { i =>
    i.name match {
      case "lb" | "lh" | "lw" | "ld" | "lbu" | "lhu" | "lwu" => MemCmd.READ
      case "sb" | "sh" | "sw" | "sd" => MemCmd.WRITE
      case "lr.w" | "lr.d" | "sc.w" | "sc.d" | "amoswap.w" => MemCmd.AMO
      case _ => MemCmd.NONE
    }
  }

  val MemSizeExp = enumField("memSize", MemSize) { i =>
    i.name match {
      case "lb" | "lbu" | "sb" => MemSize.B
      case "lh" | "lhu" | "sh" => MemSize.H
      case "lw" | "lwu" | "sw" | "lr.w" | "sc.w" | "amoswap.w" => MemSize.W
      case "ld" | "sd" | "lr.d" | "sc.d" => MemSize.D
      case _ => MemSize.B
    }
  }

  val MemSignExp = boolField("memSign") { i =>
    i.name match {
      case "lb" | "lh" | "lw" | "ld" => true
      case _ => false
    }
  }

  // [维度五：写回目标 (Writeback & Commit)]
  val WbTargetExp = enumField("wbTarget", WbTarget) { i =>
    i.name match {
      case "beq" | "bne" | "blt" | "bge" | "bltu" | "bgeu" | "sb" | "sh" | "sw" | "sd" | "ecall" | "ebreak" | "mret" | "sret" | "wfi" => WbTarget.NONE
      case "csrrw" | "csrrs" | "csrrc" | "csrrwi" | "csrrsi" | "csrrci" => WbTarget.CSR_REG
      case _ => WbTarget.INT_REG
    }
  }

  // [专用域：立即数提取信号选择]
  val ImmTypeExp = enumField("immType", ImmTypeEnum) { i =>
    val args = i.args.map(_.name)
    if (args.contains("imm12"))            ImmTypeEnum.immI
    else if (i.name == "ebreak" || i.name == "ecall") ImmTypeEnum.immI // 强制令系统陷入指令走 I-type，以便拿到 0x001 等特殊码的 imm
    else if (args.contains("imm12lo"))     ImmTypeEnum.immS
    else if (args.contains("bimm12lo"))    ImmTypeEnum.immB
    else if (args.contains("imm20"))       ImmTypeEnum.immU
    else if (args.contains("jimm20"))      ImmTypeEnum.immJ
    else if (args.contains("shamtd"))      ImmTypeEnum.immShamtD
    else if (args.contains("shamtw"))      ImmTypeEnum.immShamtW
    else if (args.contains("shamt"))       ImmTypeEnum.immShamtW // RV32 uses shamt as 5-bit
    else if (args.contains("zimm5"))       ImmTypeEnum.immZ
    else                                   ImmTypeEnum.immNone
  }

  val MduOpExp = enumField("mduOp", MduOp) { i =>
    i.name match {
      case "mul" | "mulw"       => MduOp.MUL
      case "mulh"               => MduOp.MULH
      case "mulhsu"             => MduOp.MULHSU
      case "mulhu"              => MduOp.MULHU
      case "div" | "divw"       => MduOp.DIV
      case "divu" | "divuw"     => MduOp.DIVU
      case "rem" | "remw"       => MduOp.REM
      case "remu" | "remuw"     => MduOp.REMU
      case _ => MduOp.NONE
    }
  }

  val allFields = Seq(
    FuTypeExp, Src1Exp, Src2Exp, AluOpExp, BruOpExp, CsrOpExp, MduOpExp,
    MemCmdExp, MemSizeExp, MemSignExp, WbTargetExp, ImmTypeExp
  )
}
