// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VCoreTop__Syms.h"


void VCoreTop___024root__trace_chg_0_sub_0(VCoreTop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void VCoreTop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_chg_0\n"); );
    // Init
    VCoreTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VCoreTop___024root*>(voidSelf);
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    VCoreTop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void VCoreTop___024root__trace_chg_0_sub_0(VCoreTop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_chg_0_sub_0\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg),32);
        bufp->chgIData(oldp+1,(vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp),32);
        bufp->chgCData(oldp+2,(vlSelfRef.CoreTop__DOT___idu_io_out_bits_src1Sel),2);
        bufp->chgCData(oldp+3,(vlSelfRef.CoreTop__DOT___idu_io_out_bits_src2Sel),2);
        bufp->chgCData(oldp+4,(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp),4);
        bufp->chgCData(oldp+5,(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp),4);
        bufp->chgCData(oldp+6,(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memCmd),2);
        bufp->chgCData(oldp+7,(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize),2);
        bufp->chgBit(oldp+8,(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSign));
        bufp->chgCData(oldp+9,(vlSelfRef.CoreTop__DOT___lsu_io_out_bits_wbTarget),2);
        bufp->chgBit(oldp+10,((0x100073U == vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)));
        bufp->chgCData(oldp+11,((0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                          >> 0xfU))),5);
        bufp->chgIData(oldp+12,(vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp),32);
        bufp->chgIData(oldp+13,(vlSelfRef.CoreTop__DOT___regfile_io_rs2_data),32);
        bufp->chgIData(oldp+14,(vlSelfRef.CoreTop__DOT___regfile_io_rs1_data),32);
        bufp->chgBit(oldp+15,(((1U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                ? (vlSelfRef.CoreTop__DOT___regfile_io_rs1_data 
                                   == vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                : ((2U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                    ? (vlSelfRef.CoreTop__DOT___regfile_io_rs1_data 
                                       != vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                    : ((3U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                        ? VL_LTS_III(32, vlSelfRef.CoreTop__DOT___regfile_io_rs1_data, vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                        : ((4U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                            ? VL_GTES_III(32, vlSelfRef.CoreTop__DOT___regfile_io_rs1_data, vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                            : ((5U 
                                                == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                                ? (vlSelfRef.CoreTop__DOT___regfile_io_rs1_data 
                                                   < vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                : (
                                                   (6U 
                                                    == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                                    ? 
                                                   (vlSelfRef.CoreTop__DOT___regfile_io_rs1_data 
                                                    >= vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp)) 
                                                    | (8U 
                                                       == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp)))))))))));
        bufp->chgIData(oldp+16,(((1U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                  ? vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT____VdfgRegularize_hfa6af0cb_0_0
                                  : ((2U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                      ? vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT____VdfgRegularize_hfa6af0cb_0_0
                                      : ((3U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                          ? vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT____VdfgRegularize_hfa6af0cb_0_0
                                          : ((4U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                              ? vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT____VdfgRegularize_hfa6af0cb_0_0
                                              : ((5U 
                                                  == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                                  ? vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT____VdfgRegularize_hfa6af0cb_0_0
                                                  : 
                                                 ((6U 
                                                   == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                                   ? vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT____VdfgRegularize_hfa6af0cb_0_0
                                                   : 
                                                  ((7U 
                                                    == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                                    ? vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT____VdfgRegularize_hfa6af0cb_0_0
                                                    : 
                                                   ((8U 
                                                     == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp))
                                                     ? 
                                                    (0xfffffffeU 
                                                     & (vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp 
                                                        + vlSelfRef.CoreTop__DOT___regfile_io_rs1_data))
                                                     : 0U))))))))),32);
        bufp->chgIData(oldp+17,(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp),32);
        bufp->chgIData(oldp+18,(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0),32);
        bufp->chgIData(oldp+19,(vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst),32);
        bufp->chgCData(oldp+20,((0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                          >> 0x14U))),5);
        bufp->chgIData(oldp+21,((0x3fffffffU & (~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 2U)))),30);
        bufp->chgBit(oldp+22,((2U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memCmd))));
        bufp->chgIData(oldp+23,(((0U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                  ? (((- (IData)(((IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSign) 
                                                  & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                     >> 7U)))) 
                                      << 8U) | (0xffU 
                                                & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                  : ((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                      ? (((- (IData)(
                                                     ((IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSign) 
                                                      & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                         >> 0xfU)))) 
                                          << 0x10U) 
                                         | (0xffffU 
                                            & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                      : vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))),32);
        bufp->chgIData(oldp+24,(vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata),32);
        bufp->chgBit(oldp+25,(((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memCmd)) 
                               | (2U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memCmd)))));
        bufp->chgCData(oldp+26,(((3U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                  ? 8U : ((2U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                           ? 4U : (
                                                   (1U 
                                                    == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                                    ? 2U
                                                    : 1U)))),8);
        bufp->chgIData(oldp+27,(vlSelfRef.CoreTop__DOT__lsu__DOT___dpicLSU_io_rdata),32);
        bufp->chgQData(oldp+28,((QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp))),64);
        bufp->chgQData(oldp+30,((QData)((IData)(vlSelfRef.CoreTop__DOT___regfile_io_rs2_data))),64);
        bufp->chgIData(oldp+32,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
                                [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           >> 0x14U))]),32);
        bufp->chgIData(oldp+33,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
                                [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           >> 0xfU))]),32);
        bufp->chgIData(oldp+34,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[0]),32);
        bufp->chgIData(oldp+35,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[1]),32);
        bufp->chgIData(oldp+36,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[2]),32);
        bufp->chgIData(oldp+37,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[3]),32);
        bufp->chgIData(oldp+38,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[4]),32);
        bufp->chgIData(oldp+39,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[5]),32);
        bufp->chgIData(oldp+40,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[6]),32);
        bufp->chgIData(oldp+41,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[7]),32);
        bufp->chgIData(oldp+42,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[8]),32);
        bufp->chgIData(oldp+43,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[9]),32);
        bufp->chgIData(oldp+44,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[10]),32);
        bufp->chgIData(oldp+45,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[11]),32);
        bufp->chgIData(oldp+46,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[12]),32);
        bufp->chgIData(oldp+47,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[13]),32);
        bufp->chgIData(oldp+48,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[14]),32);
        bufp->chgIData(oldp+49,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[15]),32);
        bufp->chgIData(oldp+50,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[16]),32);
        bufp->chgIData(oldp+51,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[17]),32);
        bufp->chgIData(oldp+52,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[18]),32);
        bufp->chgIData(oldp+53,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[19]),32);
        bufp->chgIData(oldp+54,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[20]),32);
        bufp->chgIData(oldp+55,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[21]),32);
        bufp->chgIData(oldp+56,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[22]),32);
        bufp->chgIData(oldp+57,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[23]),32);
        bufp->chgIData(oldp+58,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[24]),32);
        bufp->chgIData(oldp+59,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[25]),32);
        bufp->chgIData(oldp+60,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[26]),32);
        bufp->chgIData(oldp+61,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[27]),32);
        bufp->chgIData(oldp+62,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[28]),32);
        bufp->chgIData(oldp+63,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[29]),32);
        bufp->chgIData(oldp+64,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[30]),32);
        bufp->chgIData(oldp+65,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[31]),32);
    }
    bufp->chgBit(oldp+66,(vlSelfRef.clock));
    bufp->chgBit(oldp+67,(vlSelfRef.reset));
    bufp->chgIData(oldp+68,(vlSelfRef.io_commit_pc),32);
    bufp->chgBit(oldp+69,(vlSelfRef.io_commit_valid));
    bufp->chgCData(oldp+70,(vlSelfRef.io_commit_rd),5);
    bufp->chgIData(oldp+71,(vlSelfRef.io_commit_wdata),32);
    bufp->chgBit(oldp+72,(vlSelfRef.io_commit_wen));
    bufp->chgBit(oldp+73,(((IData)(vlSelfRef.io_commit_wen) 
                           & (0U != (IData)(vlSelfRef.io_commit_rd)))));
}

void VCoreTop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root__trace_cleanup\n"); );
    // Init
    VCoreTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VCoreTop___024root*>(voidSelf);
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
