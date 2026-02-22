package sCore

import chisel3._
import chisel3.util._
import chisel3.util.experimental.decode._
import org.chipsalliance.rvdecoderdb
import sCore.utils._
import sCore.utils.DecodeRules._

// -----------------------------------------------------------------------------
// 1. 传输结构体 (Bundle) - 采用正交多维解码结构
// -----------------------------------------------------------------------------
class DecodedMsg(implicit p: CoreConfig) extends CoreBundle {
  val pc        = UInt(vaddrBits.W)
  val imm       = UInt(xlen.W) // 经过统一拓展的安全立即数
  
  // 五维逻辑信号向量
  val fuType    = FUType()
  val src1Sel   = Src1Sel()
  val src2Sel   = Src2Sel()
  val aluOp     = AluOp()
  val bruOp     = BruOp()
  val csrOp     = CsrOp()
  val memCmd    = MemCmd()
  val memSize   = MemSize()
  val memSign   = Bool()
  val wbTarget  = WbTarget()
  val halt      = Bool() // ebreak指令标识
  
  // 寄存器索引
  val rs1addr   = UInt(5.W)
  val rs2addr   = UInt(5.W)
  val rdaddr    = UInt(5.W)
  val csr_addr  = UInt(12.W)
}

class ID_Bundle(implicit p: CoreConfig) extends CoreBundle {
  val in  = Flipped(if (isSingleCycle) new IF_ID_Bundle else Decoupled(new IF_ID_Bundle))
  val out = if (isSingleCycle) Output(new DecodedMsg) else Decoupled(new DecodedMsg)
}

// -----------------------------------------------------------------------------
// 主模块 IDU
// -----------------------------------------------------------------------------
class IDU()(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new ID_Bundle)
  
  // 提取当前周期或者握手过来的指令
  val inValid = if (isSingleCycle) true.B else io.in.asInstanceOf[DecoupledIO[IF_ID_Bundle]].valid
  val inData  = if (isSingleCycle) io.in.asInstanceOf[IF_ID_Bundle] else io.in.asInstanceOf[DecoupledIO[IF_ID_Bundle]].bits
  val inst    = inData.inst

  // 1. 数据驱动：从数据库加载目标指令集，并根据参数化配置过滤不需要的指令 (避免产生多余译码元件)
  val instTable = org.chipsalliance.rvdecoderdb.instructions(os.pwd / "riscv-opcodes")
  
  val baseSets = Seq("rv_i", "rv_system") ++
                 (if (hasM) Seq("rv_m") else Seq()) ++
                 (if (hasA) Seq("rv_a") else Seq()) ++
                 (if (hasZicsr) Seq("rv_zicsr") else Seq()) ++
                 (if (hasFPU) Seq("rv_f", "rv_d") else Seq())

  val archSets = if (xlen == 64) {
    Seq("rv32_i", "rv64_i") ++
    (if (hasM) Seq("rv32_m", "rv64_m") else Seq()) ++
    (if (hasA) Seq("rv32_a", "rv64_a") else Seq()) ++
    (if (hasFPU) Seq("rv32_f", "rv64_f", "rv32_d", "rv64_d") else Seq())
  } else {
    Seq("rv32_i") ++
    (if (hasM) Seq("rv32_m") else Seq()) ++
    (if (hasA) Seq("rv32_a") else Seq()) ++
    (if (hasFPU) Seq("rv32_f", "rv32_d") else Seq())
  }
  
  val rvcSets  = if (hasRVC) Seq("rv_c") else Seq()
  val targetSets = (baseSets ++ archSets ++ rvcSets).toSet

  val instList = instTable
    .filter(instr => targetSets.contains(instr.instructionSet.name))
    .filter(_.pseudoFrom.isEmpty)
    .map(Insn(_))
    .toSeq

  // 2. 一键生成硬件真值表
  val decodeTable   = new DecodeTable(instList, allFields)
  val decodedBundle = decodeTable.decode(inst)

  // 3. 构建输出负载 (Payload)
  val msg = Wire(new DecodedMsg)
  msg := DontCare // 兜底防止出现锁存器
  
  msg.pc        := inData.pc
  msg.imm       := ImmGen(inst, decodedBundle(ImmTypeExp), xlen) // 调用封装的生成器
  
  msg.rdaddr    := inst(11, 7)
  msg.rs1addr   := inst(19, 15)
  msg.rs2addr   := inst(24, 20)
  msg.csr_addr  := inst(31, 20)
  
  // 逻辑信号向量直接映射
  msg.fuType    := decodedBundle(FuTypeExp)
  msg.src1Sel   := decodedBundle(Src1Exp)
  msg.src2Sel   := decodedBundle(Src2Exp)
  msg.aluOp     := decodedBundle(AluOpExp)
  msg.bruOp     := decodedBundle(BruOpExp)
  msg.csrOp     := decodedBundle(CsrOpExp)
  msg.memCmd    := decodedBundle(MemCmdExp)
  msg.memSize   := decodedBundle(MemSizeExp)
  msg.memSign   := decodedBundle(MemSignExp)
  msg.wbTarget  := decodedBundle(WbTargetExp)
  msg.halt      := inst === "h00100073".U // 识别 EBREAK 指令

  // 4. 握手 / 连线逻辑
  if (isSingleCycle) {
    io.out.asInstanceOf[DecodedMsg] := msg
  } else {
    val outDec  = io.out.asInstanceOf[DecoupledIO[DecodedMsg]]
    val inDec   = io.in.asInstanceOf[DecoupledIO[IF_ID_Bundle]]
    
    outDec.valid := inDec.valid
    outDec.bits  := msg
    inDec.ready  := outDec.ready
  }
}