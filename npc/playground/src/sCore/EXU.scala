package sCore

import chisel3._
import chisel3.util._
import sCore.utils._

// -----------------------------------------------------------------------------
// 执行阶段传递给下一级的负载 (EX -> MEM 阶段)
// -----------------------------------------------------------------------------
class EX_MEM_Bundle(implicit p: CoreConfig) extends CoreBundle {
  val inst      = UInt(32.W)        // 透传的原始指令
  val aluOut    = UInt(xlen.W)      // ALU 的计算结果或访存地址
  val rs2Data   = UInt(xlen.W)      // 写内存(Store)时需要透传的原始 rs2 数据
  val pc        = UInt(vaddrBits.W) // 由于分支或跳转，有时需要原PC；或留给异常中断处理
  
  // 原封不动透传的用于后级的控制信号
  val rdaddr    = UInt(5.W)
  val wbTarget  = WbTarget()
  val memCmd    = MemCmd()
  val memSize   = MemSize()
  val memSign   = Bool()
  val halt      = Bool()
  
  // CSR 相关
  val csrWdata  = UInt(xlen.W)      // 写向 CSR 的数据(常为 src1)
  val csrAddr   = UInt(12.W)        // CSR 目标地址
  val csrOp     = CsrOp()           // 具体 CSR 操作
}

// -----------------------------------------------------------------------------
// 执行单元 IO 接口
// -----------------------------------------------------------------------------
class EXU_Bundle(implicit p: CoreConfig) extends CoreBundle {
  // 接收来自上一级解码的信息
  val in  = Flipped(if (isSingleCycle) new DecodedMsg else Decoupled(new DecodedMsg))
  val out = if (isSingleCycle) Output(new EX_MEM_Bundle) else Decoupled(new EX_MEM_Bundle)
  
  // 去往外部通用寄存器堆 (RegFile) 的读引脚
  // 如果采用解耦合设计，可以在流水线上保留数据或在组合电路期直接探出地址去拿
  val rs1_addr = Output(UInt(5.W))
  val rs2_addr = Output(UInt(5.W))
  val rs1_data = Input(UInt(xlen.W))
  val rs2_data = Input(UInt(xlen.W))
  
  // 发送给 IFU 的分支跳转重定向信号
  val redirect = Output(new RedirectIO)
  
  // CSR 读接口
  val csr_addr = Output(UInt(12.W))
  val csr_data = Input(UInt(xlen.W))
}

// -----------------------------------------------------------------------------
// 执行核心模块 (EXU) - 负责集成计算与操作数路由
// -----------------------------------------------------------------------------
class EXU()(implicit p: CoreConfig) extends CoreModule {
  val io = IO(new EXU_Bundle)
  
  // 握手解包
  val inValid = if (isSingleCycle) true.B else io.in.asInstanceOf[DecoupledIO[DecodedMsg]].valid
  val inData  = if (isSingleCycle) io.in.asInstanceOf[DecodedMsg] else io.in.asInstanceOf[DecoupledIO[DecodedMsg]].bits

  // 1. 发射寄存器堆 (RegFile) 获取源操作数的地址
  io.rs1_addr := inData.rs1addr
  io.rs2_addr := inData.rs2addr
  
  val rs1_val = io.rs1_data
  val rs2_val = io.rs2_data

  // CSR 的读取寻址与返回数据
  io.csr_addr := inData.csr_addr
  val csr_val = io.csr_data

  // 2. 实例化你确认完美无握手的纯直通 ALU 模块
  val alu = Module(new ALU())

  // 3. 操作数路由抉择 (Operand Routing Network)
  val src1 = WireInit(0.U(xlen.W))
  val src2 = WireInit(0.U(xlen.W))
  
  // 对于 CSRRWI 这类的特权指令，zimm 被隐式地放在 rs1_addr 段内了，这里要 Pad 一下以供组合逻辑使用
  val uimm = inData.rs1addr.pad(xlen)

  // -- 源操作数 1 的仲裁逻辑
  src1 := MuxLookup(inData.src1Sel, 0.U(xlen.W))(Seq(
    Src1Sel.RS1  -> rs1_val,
    Src1Sel.PC   -> inData.pc,
    Src1Sel.ZERO -> 0.U(xlen.W),
    Src1Sel.UIMM -> uimm,
    Src1Sel.CSR_VAL -> csr_val
  ))

  // -- 源操作数 2 的仲裁逻辑
  src2 := MuxLookup(inData.src2Sel, 0.U(xlen.W))(Seq(
    Src2Sel.RS2  -> rs2_val,
    Src2Sel.IMM  -> inData.imm,
    Src2Sel.FOUR -> 4.U(xlen.W)
  ))

  // 4. ALU 端孔对接与计算
  alu.io.src1   := src1
  alu.io.src2   := src2
  alu.io.aluOp  := inData.aluOp
  
  // 4.5 MDU 端孔对接与计算
  val mduOut = WireInit(0.U(xlen.W))
  if (p.hasM) {
    val mdu = Module(new MDU())
    mdu.io.src1   := src1
    mdu.io.src2   := src2
    mdu.io.mduOp  := inData.mduOp
    mduOut        := mdu.io.out
  }

  // TODO: 如果之后在 DecodeRules(含AllFields和decodeTable) 及 DecodedMsg 中加入了 isWord 位，此处就可以换成 inData.isWord
  alu.io.isWord := false.B

  // 5. 实例化 BRU 处理分支条件和跳转地址 (预留以接入预测失败判定)
  val bru = Module(new BRU())
  bru.io.rs1_data := Mux(inData.bruOp === BruOp.ECALL || inData.bruOp === BruOp.MRET, csr_val, rs1_val)
  bru.io.rs2_data := rs2_val
  bru.io.pc       := inData.pc
  bru.io.imm      := inData.imm
  bru.io.bruOp    := inData.bruOp
  
  // 暂时不支持分支预测，所以预留的预测口写定
  bru.io.bpd_predict_taken := false.B
  bru.io.bpd_predict_target := 0.U

  // 将重定向结果暴露给上一级 IFU，仅在当前级握手有效(单周期必为true)时生效
  io.redirect.valid  := bru.io.redirect_valid && inValid
  io.redirect.target := bru.io.redirect_target

  // 6. 组合将要发往下一级 (MEM 阶段) 的握手与负载信息
  val msgOut = Wire(new EX_MEM_Bundle)
  msgOut := DontCare 
  
  // 新鲜出炉的信息
  val isCsr = inData.fuType === FUType.CSR
  val isMdu = inData.fuType === FUType.MDU
  val aluOrMduOut = Mux(isMdu && p.hasM.B, mduOut, alu.io.out)
  msgOut.inst     := inData.inst
  msgOut.aluOut   := Mux(isCsr, csr_val, aluOrMduOut) // 若为 CSR 读则往下一级输送旧的 CSR 值，使得其得以正常落入通用寄存器
  msgOut.rs2Data  := rs2_val  // 必须把原汁原味的 rs2 读出来送去给 Store 使用
  msgOut.pc       := inData.pc
  
  // 透传上一级控制信号
  msgOut.rdaddr   := inData.rdaddr
  msgOut.wbTarget := inData.wbTarget
  msgOut.memCmd   := inData.memCmd
  msgOut.memSize  := inData.memSize
  msgOut.memSign  := inData.memSign
  msgOut.halt     := inData.halt

  // CSR 透传
  msgOut.csrWdata := src1
  msgOut.csrAddr  := inData.csr_addr
  msgOut.csrOp    := inData.csrOp

  // 7. 连线输出口
  if (isSingleCycle) {
    io.out.asInstanceOf[EX_MEM_Bundle] := msgOut
  } else {
    val outDec = io.out.asInstanceOf[DecoupledIO[EX_MEM_Bundle]]
    val inDec  = io.in.asInstanceOf[DecoupledIO[DecodedMsg]]
    
    outDec.valid := inDec.valid
    outDec.bits  := msgOut
    inDec.ready  := outDec.ready
  }
}
