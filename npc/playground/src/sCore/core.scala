package sCore

import chisel3._
import chisel3.util._
import chisel3.probe._
import sCore.utils._

// 这是一个专门用于生成单模块验证的 Top
class CoreTop()(implicit p: CoreConfig) extends Module {
  // 定义顶层观察与测试的 IO：将对 Commit（指令提交状态）的追踪信号引出
  val io = IO(new Bundle {
    val commit_pc      = Output(UInt(p.vaddrBits.W))
    val commit_inst    = Output(UInt(32.W))
    val commit_valid   = Output(Bool())
    val commit_is_store= Output(Bool())
    val commit_halt    = Output(Bool())
    
    // GPR 监控探针
    val commit_rd      = Output(UInt(5.W))
    val commit_wdata   = Output(UInt(p.xlen.W))
    val commit_wen     = Output(Bool())
    
    // CSR 监控探针
    val commit_csr_waddr = Output(UInt(12.W))
    val commit_csr_wdata = Output(UInt(p.xlen.W))
    val commit_csr_wen   = Output(Bool())
  })

  // ================= 1. 实例化核心组件 =================
  val ifu     = Module(new IF())
  val idu     = Module(new IDU())
  val exu     = Module(new EXU())
  val lsu     = Module(new LSU())
  val wbu     = Module(new WBU())
  val regfile = Module(new RegFile())
  val csrfile = if (p.hasZicsr) Some(Module(new CSRFile())) else None

  // ================= 2. 静态/纯直通内部连线 =================
  
  // (A) RegFile 读取网络 (解码送去给执行)
  val iduOutMsg = if (p.isSingleCycle) idu.io.out.asInstanceOf[DecodedMsg] else idu.io.out.asInstanceOf[DecoupledIO[DecodedMsg]].bits
  regfile.io.rs1_addr := iduOutMsg.rs1addr
  regfile.io.rs2_addr := iduOutMsg.rs2addr
  exu.io.rs1_data     := regfile.io.rs1_data
  exu.io.rs2_data     := regfile.io.rs2_data

  // (B) RegFile 写回网络 (写回送回给寄存器堆)
  regfile.io.rd_addr  := wbu.io.rf_waddr
  regfile.io.rd_data  := wbu.io.rf_wdata
  regfile.io.rd_wen   := wbu.io.rf_wen

  // (C) 部分反馈网络和顶层信号
  ifu.io.redirectEX <> exu.io.redirect
  ifu.io.redirectWB.valid := false.B // 目前尚未处理来自 WB 的全局冲刷(如 mret)
  ifu.io.redirectWB.target := 0.U

  // (D) CSR 连线
  if (p.hasZicsr) {
    val csr = csrfile.get
    // 读线路 (由 EXU 给出地址获取数据)
    csr.io.csr_raddr := exu.io.csr_addr
    exu.io.csr_data  := csr.io.csr_rdata
    
    // 写线路 (由 WBU 提交写入)
    csr.io.csr_waddr := wbu.io.csr_waddr
    csr.io.csr_wdata := wbu.io.csr_wdata
    csr.io.csr_wen   := wbu.io.csr_wen
    csr.io.csr_op    := wbu.io.csr_op
    
    // 接入由写回阶段解析发出的异常与特权相关接口
    csr.io.exception := wbu.io.wb_exception
    csr.io.epc       := wbu.io.wb_epc
    csr.io.cause     := wbu.io.wb_cause
  } else {
    exu.io.csr_data := 0.U
  }

  // ================= 3. 数据流打通 (Datapath) =================
  if (p.isSingleCycle) {
    // ---- [ IF ] ===> [ ID ] ----
    val iduIn = idu.io.in.asInstanceOf[IF_ID_Bundle]
    iduIn.pc   := ifu.io.sc_pc.get
    iduIn.inst := ifu.io.sc_inst.get
    
    // ---- [ ID ] ===> [ EX ] ----
    val iduOut = idu.io.out.asInstanceOf[DecodedMsg]
    val exuIn  = exu.io.in.asInstanceOf[DecodedMsg]
    exuIn := iduOut
    
    // ---- [ EX ] ===> [ MEM/LSU ] ----
    val exuOut = exu.io.out.asInstanceOf[EX_MEM_Bundle]
    val lsuIn  = lsu.io.in.asInstanceOf[EX_MEM_Bundle]
    lsuIn := exuOut

    // ---- [ MEM/LSU ] ===> [ WB ] ----
    val lsuOut = lsu.io.out.asInstanceOf[MEM_WB_Bundle]
    val wbuIn  = wbu.io.in.asInstanceOf[MEM_WB_Bundle]
    wbuIn := lsuOut
    
  } else if (p.isMultiCycle) {
    // -------------------------------------------------------------
    // 多周期握手模式 (简易版)：只有当 WBU 提交完成时，才允许 IFU 取下一条
    // -------------------------------------------------------------
    
    // 令牌：是否允许取新指令
    val allowFetch = RegInit(true.B)
    
    // 队列充当级联缓存 (Pipeline Registers)
    // 禁用 pipe=true 使得 Queue 真正发挥锁存一拍的作用，形成阶梯流水流转
    val if_id_q = Module(new Queue(new IF_ID_Bundle, 1))
    val id_ex_q = Module(new Queue(new DecodedMsg, 1))
    val ex_mem_q= Module(new Queue(new EX_MEM_Bundle, 1))
    val mem_wb_q= Module(new Queue(new MEM_WB_Bundle, 1))

    // 绑定内部 Queue 冲刷接口 (检测异常或跳转清空级联状态)
    // 多周期模式下只允许 1 条在途指令，重定向时不应清除“当前”指令本身，
    // 否则会丢失 commit（例如 JAL 被 flush 掉，导致提交序列缺失）。
    // 因此只清空前端级（IF/ID、ID/EX），保留后端级的在途指令。
    val flushFront = ifu.io.redirectEX.valid || ifu.io.redirectWB.valid
    if_id_q.reset  := reset.asBool || flushFront
    id_ex_q.reset  := reset.asBool || flushFront
    ex_mem_q.reset := reset.asBool
    mem_wb_q.reset := reset.asBool

    // -------- [ 发射控制 ] --------
    // 拦截 IFU 发出的握手请求，当不允许取指时，强制屏蔽它的 valid，使其在这拍堵塞
    val ifuOut = ifu.io.nextStage.get
    if_id_q.io.enq.valid := ifuOut.valid && allowFetch
    if_id_q.io.enq.bits  := ifuOut.bits
    
    // 仅在允许发射且队列接收时，IFU 才被认为是真正“发出去”了
    ifuOut.ready         := if_id_q.io.enq.ready && allowFetch

    // -------- [ 级间队列连线 ] --------
    // ID 阶
    val iduInDec = idu.io.in.asInstanceOf[DecoupledIO[IF_ID_Bundle]]
    iduInDec <> if_id_q.io.deq
    
    id_ex_q.io.enq <> idu.io.out.asInstanceOf[DecoupledIO[DecodedMsg]]

    // EX 阶
    val exuInDec = exu.io.in.asInstanceOf[DecoupledIO[DecodedMsg]]
    exuInDec <> id_ex_q.io.deq
    
    ex_mem_q.io.enq <> exu.io.out.asInstanceOf[DecoupledIO[EX_MEM_Bundle]]

    // MEM(LSU) 阶
    val lsuInDec = lsu.io.in.asInstanceOf[DecoupledIO[EX_MEM_Bundle]]
    lsuInDec <> ex_mem_q.io.deq
    
    mem_wb_q.io.enq <> lsu.io.out.asInstanceOf[DecoupledIO[MEM_WB_Bundle]]

    // WB 阶
    val wbuInDec = wbu.io.in.asInstanceOf[DecoupledIO[MEM_WB_Bundle]]
    wbuInDec <> mem_wb_q.io.deq

    // -----------------------------------------------------------------------
    // 令牌状态机（修复版）
    //
    // Bug 根源：Chisel Queue(T,1) 空队列时允许 enq/deq 在同一拍 fire（zero-
    // latency bypass），且各级 inDec.ready := outDec.ready 组合穿透。这导致：
    // 1. 发指令（if_id_q.enq.fire）与 WBU 接收（wbuInDec.fire）同拍成立
    // 2. 原来两个独立 when 块中 Chisel 语义「后者覆盖前者」：
    //      when(enq.fire)  { allowFetch := false.B }  // 先
    //      when(wbu.fire)  { allowFetch := true.B  }  // 后 → 覆盖 → 令牌永不丢失
    //
    // 修复：改用 when-elsewhen，保证「没收」拥有最高优先级，
    // 发射新指令的那一拍，归还动作绝对不会同时生效。
    // -----------------------------------------------------------------------
    when(if_id_q.io.enq.fire) {
      // 最高优先级：IFU 在此拍成功发射了一条指令 → 没收令牌
      allowFetch := false.B
    } .elsewhen(wbuInDec.fire) {
      // 仅当本拍没有同时发射新指令时，才归还令牌（或 flush 清空流水线时复位）
      allowFetch := true.B
    }
  } else {
    // -------------------------------------------------------------
    // 标准解耦流水线模式 (Pipeline)
    // -------------------------------------------------------------
    // ID 阶
    val iduInDec = idu.io.in.asInstanceOf[DecoupledIO[IF_ID_Bundle]]
    iduInDec <> ifu.io.nextStage.get
    
    // EX 阶
    val exuInDec = exu.io.in.asInstanceOf[DecoupledIO[DecodedMsg]]
    exuInDec <> idu.io.out.asInstanceOf[DecoupledIO[DecodedMsg]]
    
    // MEM(LSU) 阶
    val lsuInDec = lsu.io.in.asInstanceOf[DecoupledIO[EX_MEM_Bundle]]
    lsuInDec <> exu.io.out.asInstanceOf[DecoupledIO[EX_MEM_Bundle]]

    // WB 阶
    val wbuInDec = wbu.io.in.asInstanceOf[DecoupledIO[MEM_WB_Bundle]]
    wbuInDec <> lsu.io.out.asInstanceOf[DecoupledIO[MEM_WB_Bundle]]
  }

  // ================= 4. 测试与观察层投射 =================
  io.commit_pc       := wbu.io.wb_pc
  io.commit_inst     := wbu.io.wb_inst
  io.commit_valid    := wbu.io.wb_valid
  io.commit_is_store := wbu.io.wb_is_store
  io.commit_halt     := wbu.io.wb_halt
  
  io.commit_rd       := wbu.io.rf_waddr
  io.commit_wdata    := wbu.io.rf_wdata
  io.commit_wen      := wbu.io.rf_wen
  
  if (p.hasZicsr) {
    io.commit_csr_waddr := wbu.io.csr_waddr
    io.commit_csr_wdata := wbu.io.csr_wdata
    io.commit_csr_wen   := wbu.io.csr_wen
  } else {
    io.commit_csr_waddr := 0.U
    io.commit_csr_wdata := 0.U
    io.commit_csr_wen   := false.B
  }
}
