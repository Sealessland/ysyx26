// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VCoreTop__Syms.h"


VL_ATTR_COLD void VCoreTop___024root__trace_init_sub__TOP__0(VCoreTop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_init_sub__TOP__0\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+86,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+88,0,"io_commit_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+89,0,"io_commit_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+90,0,"io_commit_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+91,0,"io_commit_is_store",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"io_commit_halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+93,0,"io_commit_rd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+94,0,"io_commit_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+95,0,"io_commit_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+96,0,"io_commit_csr_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+97,0,"io_commit_csr_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+98,0,"io_commit_csr_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("CoreTop", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+86,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+88,0,"io_commit_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+89,0,"io_commit_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+90,0,"io_commit_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+91,0,"io_commit_is_store",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"io_commit_halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+93,0,"io_commit_rd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+94,0,"io_commit_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+95,0,"io_commit_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+96,0,"io_commit_csr_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+97,0,"io_commit_csr_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+98,0,"io_commit_csr_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("csrfile", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+86,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+96,0,"io_csr_raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+1,0,"io_csr_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"io_csr_waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+2,0,"io_csr_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+98,0,"io_csr_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+3,0,"io_csr_op",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+4,0,"io_exception",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"io_epc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+6,0,"mstatus",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+7,0,"mtvec",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+8,0,"mepc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+9,0,"mcause",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+1,0,"old_val",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"new_val",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("exu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+11,0,"io_in_inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"io_in_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+12,0,"io_in_imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+13,0,"io_in_fuType",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+14,0,"io_in_src1Sel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+15,0,"io_in_src2Sel",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+16,0,"io_in_aluOp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+17,0,"io_in_bruOp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+3,0,"io_in_csrOp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+18,0,"io_in_mduOp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+19,0,"io_in_memCmd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+20,0,"io_in_memSize",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+21,0,"io_in_memSign",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+22,0,"io_in_wbTarget",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+92,0,"io_in_halt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+23,0,"io_in_rs1addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+93,0,"io_in_rdaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+96,0,"io_in_csr_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+11,0,"io_out_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+24,0,"io_out_aluOut",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+25,0,"io_out_rs2Data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"io_out_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+93,0,"io_out_rdaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+22,0,"io_out_wbTarget",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+19,0,"io_out_memCmd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+20,0,"io_out_memSize",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+21,0,"io_out_memSign",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"io_out_halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+2,0,"io_out_csrWdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"io_out_csrAddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+3,0,"io_out_csrOp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+26,0,"io_rs1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+25,0,"io_rs2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+27,0,"io_redirect_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+28,0,"io_redirect_target",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"io_csr_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+1,0,"io_csr_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+2,0,"casez_tmp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+29,0,"casez_tmp_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("alu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+2,0,"io_src1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+29,0,"io_src2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+16,0,"io_aluOp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+30,0,"io_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+30,0,"casez_tmp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("bru", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+31,0,"io_rs1_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+25,0,"io_rs2_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"io_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+12,0,"io_imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+17,0,"io_bruOp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+27,0,"io_redirect_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+28,0,"io_redirect_target",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+28,0,"casez_tmp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("mdu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+2,0,"io_src1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+29,0,"io_src2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+18,0,"io_mduOp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+32,0,"io_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+33,0,"isDivZero",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"isOverflow",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+35,0,"mulUnS",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("idu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+86,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"io_in_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+11,0,"io_in_inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+11,0,"io_out_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"io_out_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+12,0,"io_out_imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+13,0,"io_out_fuType",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+14,0,"io_out_src1Sel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+15,0,"io_out_src2Sel",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+16,0,"io_out_aluOp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+17,0,"io_out_bruOp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+3,0,"io_out_csrOp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+18,0,"io_out_mduOp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+19,0,"io_out_memCmd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+20,0,"io_out_memSize",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+21,0,"io_out_memSign",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+22,0,"io_out_wbTarget",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+92,0,"io_out_halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+23,0,"io_out_rs1addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+37,0,"io_out_rs2addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+93,0,"io_out_rdaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+96,0,"io_out_csr_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+38,0,"decodedBundle_invInputs",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 29,0);
    tracep->declBus(c+3,0,"msg_csrOp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+39,0,"decodedBundle_wbTarget",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+12,0,"casez_tmp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+92,0,"msg_halt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("ifu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+86,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+11,0,"io_sc_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"io_sc_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+27,0,"io_redirectEX_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+28,0,"io_redirectEX_target",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"pcReg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("fetchUnit", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+5,0,"io_mem_req_bits_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+11,0,"io_mem_resp_bits_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("dpic", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+5,0,"io_raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+11,0,"io_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("lsu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+86,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+11,0,"io_in_inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+24,0,"io_in_aluOut",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+25,0,"io_in_rs2Data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"io_in_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+93,0,"io_in_rdaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+22,0,"io_in_wbTarget",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+19,0,"io_in_memCmd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+20,0,"io_in_memSize",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+21,0,"io_in_memSign",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"io_in_halt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+2,0,"io_in_csrWdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"io_in_csrAddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+3,0,"io_in_csrOp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+11,0,"io_out_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+94,0,"io_out_rfData",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"io_out_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+93,0,"io_out_rdaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+22,0,"io_out_wbTarget",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+92,0,"io_out_halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+2,0,"io_out_csrWdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"io_out_csrAddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+3,0,"io_out_csrOp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+19,0,"io_out_memCmd",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+40,0,"dpicLSU_io_cmd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+41,0,"casez_tmp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+42,0,"shiftedRdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("dpicLSU", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+100,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+100,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+86,0,"io_clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+43,0,"io_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+40,0,"io_cmd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+24,0,"io_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+25,0,"io_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+44,0,"io_len",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+45,0,"io_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+46,0,"addr_64",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+48,0,"wdata_64",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+50,0,"aligned_raddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+101,0,"aligned_rlen",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("regfile", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+86,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+23,0,"io_rs1_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+26,0,"io_rs1_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+37,0,"io_rs2_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+25,0,"io_rs2_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+93,0,"io_rd_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+94,0,"io_rd_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+95,0,"io_rd_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("regs_ext", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+37,0,"R0_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+102,0,"R0_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+86,0,"R0_clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+52,0,"R0_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+23,0,"R1_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+102,0,"R1_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+86,0,"R1_clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+53,0,"R1_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+93,0,"W0_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+99,0,"W0_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+86,0,"W0_clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+94,0,"W0_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("Memory", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+54+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("wbu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+86,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+11,0,"io_in_inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+94,0,"io_in_rfData",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"io_in_pc",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+93,0,"io_in_rdaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+22,0,"io_in_wbTarget",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+92,0,"io_in_halt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+2,0,"io_in_csrWdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"io_in_csrAddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+3,0,"io_in_csrOp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+19,0,"io_in_memCmd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+88,0,"io_wb_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+89,0,"io_wb_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+91,0,"io_wb_is_store",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"io_wb_halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+4,0,"io_wb_exception",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+5,0,"io_wb_epc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+93,0,"io_rf_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+94,0,"io_rf_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+95,0,"io_rf_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+96,0,"io_csr_waddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+2,0,"io_csr_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+98,0,"io_csr_wen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+3,0,"io_csr_op",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->pushPrefix("dpicEbreak", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+86,0,"io_clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"io_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void VCoreTop___024root__trace_init_top(VCoreTop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_init_top\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VCoreTop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void VCoreTop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void VCoreTop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VCoreTop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VCoreTop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void VCoreTop___024root__trace_register(VCoreTop___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_register\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&VCoreTop___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&VCoreTop___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&VCoreTop___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&VCoreTop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void VCoreTop___024root__trace_const_0_sub_0(VCoreTop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VCoreTop___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_const_0\n"); );
    // Init
    VCoreTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VCoreTop___024root*>(voidSelf);
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    VCoreTop___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VCoreTop___024root__trace_const_0_sub_0(VCoreTop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_const_0_sub_0\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+100,(0x20U),32);
    bufp->fullCData(oldp+101,(4U),8);
    bufp->fullBit(oldp+102,(1U));
}

VL_ATTR_COLD void VCoreTop___024root__trace_full_0_sub_0(VCoreTop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VCoreTop___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_full_0\n"); );
    // Init
    VCoreTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VCoreTop___024root*>(voidSelf);
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    VCoreTop___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VCoreTop___024root__trace_full_0_sub_0(VCoreTop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_full_0_sub_0\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+1,(vlSelfRef.CoreTop__DOT___csrfile_io_csr_rdata),32);
    bufp->fullIData(oldp+2,(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp),32);
    bufp->fullCData(oldp+3,(vlSelfRef.CoreTop__DOT___wbu_io_csr_op),3);
    bufp->fullBit(oldp+4,((0x73U == vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)));
    bufp->fullIData(oldp+5,(vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg),32);
    bufp->fullIData(oldp+6,(vlSelfRef.CoreTop__DOT__csrfile__DOT__mstatus),32);
    bufp->fullIData(oldp+7,(vlSelfRef.CoreTop__DOT__csrfile__DOT__mtvec),32);
    bufp->fullIData(oldp+8,(vlSelfRef.CoreTop__DOT__csrfile__DOT__mepc),32);
    bufp->fullIData(oldp+9,(vlSelfRef.CoreTop__DOT__csrfile__DOT__mcause),32);
    bufp->fullIData(oldp+10,(vlSelfRef.CoreTop__DOT__csrfile__DOT__new_val),32);
    bufp->fullIData(oldp+11,(vlSelfRef.CoreTop__DOT___ifu_io_sc_inst),32);
    bufp->fullIData(oldp+12,(vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp),32);
    bufp->fullCData(oldp+13,(vlSelfRef.CoreTop__DOT___idu_io_out_fuType),3);
    bufp->fullCData(oldp+14,(vlSelfRef.CoreTop__DOT___idu_io_out_src1Sel),3);
    bufp->fullCData(oldp+15,(vlSelfRef.CoreTop__DOT___idu_io_out_src2Sel),2);
    bufp->fullCData(oldp+16,(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp),4);
    bufp->fullCData(oldp+17,(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp),4);
    bufp->fullCData(oldp+18,(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp),4);
    bufp->fullCData(oldp+19,(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd),2);
    bufp->fullCData(oldp+20,(vlSelfRef.CoreTop__DOT___exu_io_out_memSize),2);
    bufp->fullBit(oldp+21,((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4))));
    bufp->fullCData(oldp+22,(((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_3)
                               ? 1U : (IData)(vlSelfRef.CoreTop__DOT__idu__DOT__decodedBundle_wbTarget))),2);
    bufp->fullCData(oldp+23,((0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 0xfU))),5);
    bufp->fullIData(oldp+24,(vlSelfRef.CoreTop__DOT___exu_io_out_aluOut),32);
    bufp->fullIData(oldp+25,(vlSelfRef.CoreTop__DOT___regfile_io_rs2_data),32);
    bufp->fullIData(oldp+26,(vlSelfRef.CoreTop__DOT___regfile_io_rs1_data),32);
    bufp->fullBit(oldp+27,(((1U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                             ? (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                == vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                             : ((2U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                 ? (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                    != vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                 : ((3U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                     ? VL_LTS_III(32, vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data, vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                     : ((4U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                         ? VL_GTES_III(32, vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data, vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                         : ((5U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                             ? (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                                < vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                             : ((6U 
                                                 == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                 ? 
                                                (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                                 >= vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                 : 
                                                ((7U 
                                                  == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp)) 
                                                 | ((8U 
                                                     == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp)) 
                                                    | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_4)))))))))));
    bufp->fullIData(oldp+28,(((8U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                               ? ((4U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                   ? 0U : ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                            ? ((1U 
                                                & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                ? 0U
                                                : vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data)
                                            : ((1U 
                                                & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                ? vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data
                                                : (0xfffffffeU 
                                                   & (vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp 
                                                      + vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data)))))
                               : ((4U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                   ? ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                       ? ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                           ? (vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg 
                                              + vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp)
                                           : (vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg 
                                              + vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp))
                                       : ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                           ? (vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg 
                                              + vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp)
                                           : (vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg 
                                              + vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp)))
                                   : ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                       ? ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                           ? (vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg 
                                              + vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp)
                                           : (vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg 
                                              + vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp))
                                       : ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                           ? (vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg 
                                              + vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp)
                                           : 0U))))),32);
    bufp->fullIData(oldp+29,(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0),32);
    bufp->fullIData(oldp+30,(vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp),32);
    bufp->fullIData(oldp+31,(vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data),32);
    bufp->fullIData(oldp+32,(((8U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                               ? ((0U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                   ? vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp
                                   : VL_MODDIV_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                               : ((7U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                   ? ((0U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                       ? vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp
                                       : ((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow)
                                           ? 0U : VL_MODDIVS_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))
                                   : ((6U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                       ? ((0U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                           ? 0xffffffffU
                                           : VL_DIV_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                                       : ((5U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                           ? ((0U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                               ? 0xffffffffU
                                               : ((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow)
                                                   ? vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp
                                                   : (IData)(
                                                             (0x1ffffffffULL 
                                                              & VL_DIVS_QQQ(33, 
                                                                            (((QData)((IData)(
                                                                                (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                                                                                >> 0x1fU))) 
                                                                              << 0x20U) 
                                                                             | (QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp))), 
                                                                            (((QData)((IData)(
                                                                                (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0 
                                                                                >> 0x1fU))) 
                                                                              << 0x20U) 
                                                                             | (QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))))))))
                                           : ((4U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                               ? (IData)(
                                                         (((QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp)) 
                                                           * (QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))) 
                                                          >> 0x20U))
                                               : ((3U 
                                                   == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                                   ? (IData)(
                                                             ((vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT___GEN 
                                                               * (QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))) 
                                                              >> 0x20U))
                                                   : 
                                                  ((2U 
                                                    == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                                    ? (IData)(
                                                              ((vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT___GEN 
                                                                * 
                                                                (((QData)((IData)(
                                                                                (- (IData)(
                                                                                (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0 
                                                                                >> 0x1fU))))) 
                                                                  << 0x20U) 
                                                                 | (QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))) 
                                                               >> 0x20U))
                                                    : 
                                                   ((1U 
                                                     == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                                     ? 
                                                    (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                                                     * vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                                     : 0U))))))))),32);
    bufp->fullBit(oldp+33,((0U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)));
    bufp->fullBit(oldp+34,(vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow));
    bufp->fullQData(oldp+35,(((QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp)) 
                              * (QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))),64);
    bufp->fullCData(oldp+37,((0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 0x14U))),5);
    bufp->fullIData(oldp+38,((0x3fffffffU & (~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                >> 2U)))),30);
    bufp->fullCData(oldp+39,(vlSelfRef.CoreTop__DOT__idu__DOT__decodedBundle_wbTarget),2);
    bufp->fullBit(oldp+40,((2U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd))));
    bufp->fullIData(oldp+41,(((0U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                               ? (((- (IData)(((0xffU 
                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                               & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                  >> 7U)))) 
                                   << 8U) | (0xffU 
                                             & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                               : ((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                   ? (((- (IData)((
                                                   (0xffU 
                                                    == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                                   & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                      >> 0xfU)))) 
                                       << 0x10U) | 
                                      (0xffffU & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                   : vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))),32);
    bufp->fullIData(oldp+42,(vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata),32);
    bufp->fullBit(oldp+43,(((1U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd)) 
                            | (2U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd)))));
    bufp->fullCData(oldp+44,(((3U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                               ? 8U : ((2U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                        ? 4U : ((1U 
                                                 == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                                 ? 2U
                                                 : 1U)))),8);
    bufp->fullIData(oldp+45,(vlSelfRef.CoreTop__DOT__lsu__DOT___dpicLSU_io_rdata),32);
    bufp->fullQData(oldp+46,((QData)((IData)(vlSelfRef.CoreTop__DOT___exu_io_out_aluOut))),64);
    bufp->fullQData(oldp+48,((QData)((IData)(vlSelfRef.CoreTop__DOT___regfile_io_rs2_data))),64);
    bufp->fullQData(oldp+50,((QData)((IData)((0xfffffffcU 
                                              & vlSelfRef.CoreTop__DOT___exu_io_out_aluOut)))),64);
    bufp->fullIData(oldp+52,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
                             [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                        >> 0x14U))]),32);
    bufp->fullIData(oldp+53,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
                             [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                        >> 0xfU))]),32);
    bufp->fullIData(oldp+54,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[0]),32);
    bufp->fullIData(oldp+55,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[1]),32);
    bufp->fullIData(oldp+56,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[2]),32);
    bufp->fullIData(oldp+57,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[3]),32);
    bufp->fullIData(oldp+58,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[4]),32);
    bufp->fullIData(oldp+59,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[5]),32);
    bufp->fullIData(oldp+60,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[6]),32);
    bufp->fullIData(oldp+61,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[7]),32);
    bufp->fullIData(oldp+62,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[8]),32);
    bufp->fullIData(oldp+63,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[9]),32);
    bufp->fullIData(oldp+64,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[10]),32);
    bufp->fullIData(oldp+65,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[11]),32);
    bufp->fullIData(oldp+66,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[12]),32);
    bufp->fullIData(oldp+67,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[13]),32);
    bufp->fullIData(oldp+68,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[14]),32);
    bufp->fullIData(oldp+69,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[15]),32);
    bufp->fullIData(oldp+70,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[16]),32);
    bufp->fullIData(oldp+71,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[17]),32);
    bufp->fullIData(oldp+72,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[18]),32);
    bufp->fullIData(oldp+73,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[19]),32);
    bufp->fullIData(oldp+74,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[20]),32);
    bufp->fullIData(oldp+75,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[21]),32);
    bufp->fullIData(oldp+76,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[22]),32);
    bufp->fullIData(oldp+77,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[23]),32);
    bufp->fullIData(oldp+78,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[24]),32);
    bufp->fullIData(oldp+79,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[25]),32);
    bufp->fullIData(oldp+80,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[26]),32);
    bufp->fullIData(oldp+81,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[27]),32);
    bufp->fullIData(oldp+82,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[28]),32);
    bufp->fullIData(oldp+83,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[29]),32);
    bufp->fullIData(oldp+84,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[30]),32);
    bufp->fullIData(oldp+85,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[31]),32);
    bufp->fullBit(oldp+86,(vlSelfRef.clock));
    bufp->fullBit(oldp+87,(vlSelfRef.reset));
    bufp->fullIData(oldp+88,(vlSelfRef.io_commit_pc),32);
    bufp->fullIData(oldp+89,(vlSelfRef.io_commit_inst),32);
    bufp->fullBit(oldp+90,(vlSelfRef.io_commit_valid));
    bufp->fullBit(oldp+91,(vlSelfRef.io_commit_is_store));
    bufp->fullBit(oldp+92,(vlSelfRef.io_commit_halt));
    bufp->fullCData(oldp+93,(vlSelfRef.io_commit_rd),5);
    bufp->fullIData(oldp+94,(vlSelfRef.io_commit_wdata),32);
    bufp->fullBit(oldp+95,(vlSelfRef.io_commit_wen));
    bufp->fullSData(oldp+96,(vlSelfRef.io_commit_csr_waddr),12);
    bufp->fullIData(oldp+97,(vlSelfRef.io_commit_csr_wdata),32);
    bufp->fullBit(oldp+98,(vlSelfRef.io_commit_csr_wen));
    bufp->fullBit(oldp+99,(((IData)(vlSelfRef.io_commit_wen) 
                            & (0U != (IData)(vlSelfRef.io_commit_rd)))));
}
