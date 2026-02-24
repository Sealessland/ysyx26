package sCore

import chisel3._
import chisel3.util._
import chisel3.probe._
import sCore.utils._

// 这是一个专门用于生成单模块验证的 Top
class CoreTop()(implicit p: CoreConfig) extends Module {
  // 定义顶层观察与测试的 IO：将对 Commit（指令提交状态）的追踪信号引出
  val io = IO(new Bundle {
    val commit_pc    = Output(UInt(p.vaddrBits.W))
    val commit_valid = Output(Bool())
    
    // GPR 监控探针
    val commit_rd    = Output(UInt(5.W))
    val commit_wdata = Output(UInt(p.xlen.W))
    val commit_wen   = Output(Bool())
    
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
    
    // 尚未处理异常和特权相关的接口，先写死 0
    csr.io.exception := false.B
    csr.io.epc       := 0.U
    csr.io.cause     := 0.U
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
    
  } else {
    // 握手模式：IFU -> IDU -> EXU -> LSU -> WBU
    val iduInDec = idu.io.in.asInstanceOf[DecoupledIO[IF_ID_Bundle]]
    iduInDec <> ifu.io.nextStage.get
    
    val exuInDec = exu.io.in.asInstanceOf[DecoupledIO[DecodedMsg]]
    exuInDec <> idu.io.out.asInstanceOf[DecoupledIO[DecodedMsg]]
    
    val lsuInDec = lsu.io.in.asInstanceOf[DecoupledIO[EX_MEM_Bundle]]
    lsuInDec <> exu.io.out.asInstanceOf[DecoupledIO[EX_MEM_Bundle]]

    val wbuInDec = wbu.io.in.asInstanceOf[DecoupledIO[MEM_WB_Bundle]]
    wbuInDec <> lsu.io.out.asInstanceOf[DecoupledIO[MEM_WB_Bundle]]
  }

  // ================= 4. 测试与观察层投射 =================
  io.commit_pc    := wbu.io.wb_pc
  io.commit_valid := wbu.io.wb_valid
  
  io.commit_rd    := wbu.io.rf_waddr
  io.commit_wdata := wbu.io.rf_wdata
  io.commit_wen   := wbu.io.rf_wen
  if (p.hasZicsr) {
    // 仅在参数化开启时，在顶层动态附加生成用于 DPI/Verilator 监控的探针端口
    val probe_csr_waddr = IO(Output(Probe(UInt(12.W))))
    val probe_csr_wdata = IO(Output(Probe(UInt(p.xlen.W))))
    val probe_csr_wen   = IO(Output(Probe(Bool())))
    val probe_csr_op    = IO(Output(Probe(CsrOp())))

    define(probe_csr_waddr, ProbeValue(wbu.io.csr_waddr))
    define(probe_csr_wdata, ProbeValue(wbu.io.csr_wdata))
    define(probe_csr_wen,   ProbeValue(wbu.io.csr_wen))
    define(probe_csr_op,    ProbeValue(wbu.io.csr_op))
  }
}
