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
        bufp->chgIData(oldp+0,(vlSelfRef.CoreTop__DOT___csrfile_io_csr_rdata),32);
        bufp->chgIData(oldp+1,(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp),32);
        bufp->chgCData(oldp+2,(vlSelfRef.CoreTop__DOT___wbu_io_csr_op),3);
        bufp->chgBit(oldp+3,((0x73U == vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)));
        bufp->chgIData(oldp+4,(vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg),32);
        bufp->chgIData(oldp+5,(vlSelfRef.CoreTop__DOT__csrfile__DOT__mstatus),32);
        bufp->chgIData(oldp+6,(vlSelfRef.CoreTop__DOT__csrfile__DOT__mtvec),32);
        bufp->chgIData(oldp+7,(vlSelfRef.CoreTop__DOT__csrfile__DOT__mepc),32);
        bufp->chgIData(oldp+8,(vlSelfRef.CoreTop__DOT__csrfile__DOT__mcause),32);
        bufp->chgIData(oldp+9,(vlSelfRef.CoreTop__DOT__csrfile__DOT__new_val),32);
        bufp->chgIData(oldp+10,(vlSelfRef.CoreTop__DOT___ifu_io_sc_inst),32);
        bufp->chgIData(oldp+11,(vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp),32);
        bufp->chgCData(oldp+12,(vlSelfRef.CoreTop__DOT___idu_io_out_fuType),3);
        bufp->chgCData(oldp+13,(vlSelfRef.CoreTop__DOT___idu_io_out_src1Sel),3);
        bufp->chgCData(oldp+14,(vlSelfRef.CoreTop__DOT___idu_io_out_src2Sel),2);
        bufp->chgCData(oldp+15,(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp),4);
        bufp->chgCData(oldp+16,(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp),4);
        bufp->chgCData(oldp+17,(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp),4);
        bufp->chgCData(oldp+18,(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd),2);
        bufp->chgCData(oldp+19,(vlSelfRef.CoreTop__DOT___exu_io_out_memSize),2);
        bufp->chgBit(oldp+20,((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4))));
        bufp->chgCData(oldp+21,(((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_3)
                                  ? 1U : (IData)(vlSelfRef.CoreTop__DOT__idu__DOT__decodedBundle_wbTarget))),2);
        bufp->chgCData(oldp+22,((0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                          >> 0xfU))),5);
        bufp->chgIData(oldp+23,(vlSelfRef.CoreTop__DOT___exu_io_out_aluOut),32);
        bufp->chgIData(oldp+24,(vlSelfRef.CoreTop__DOT___regfile_io_rs2_data),32);
        bufp->chgIData(oldp+25,(vlSelfRef.CoreTop__DOT___regfile_io_rs1_data),32);
        bufp->chgBit(oldp+26,(((1U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                ? (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                   == vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                : ((2U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                    ? (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                       != vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                    : ((3U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                        ? VL_LTS_III(32, vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data, vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                        : ((4U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                            ? VL_GTES_III(32, vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data, vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                            : ((5U 
                                                == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                ? (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                                   < vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                : (
                                                   (6U 
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
        bufp->chgIData(oldp+27,(((8U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                  ? ((4U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                      ? 0U : ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                               ? ((1U 
                                                   & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                   ? 0U
                                                   : vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data)
                                               : ((1U 
                                                   & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                   ? vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data
                                                   : 
                                                  (0xfffffffeU 
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
        bufp->chgIData(oldp+28,(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0),32);
        bufp->chgIData(oldp+29,(vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp),32);
        bufp->chgIData(oldp+30,(vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data),32);
        bufp->chgIData(oldp+31,(((8U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                  ? ((0U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                      ? vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp
                                      : VL_MODDIV_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                                  : ((7U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                      ? ((0U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                          ? vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp
                                          : ((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow)
                                              ? 0U : 
                                             VL_MODDIVS_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))
                                      : ((6U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                          ? ((0U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                              ? 0xffffffffU
                                              : VL_DIV_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                                          : ((5U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                              ? ((0U 
                                                  == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                                  ? 0xffffffffU
                                                  : 
                                                 ((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow)
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
                                              : ((4U 
                                                  == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                                  ? (IData)(
                                                            (((QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp)) 
                                                              * (QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))) 
                                                             >> 0x20U))
                                                  : 
                                                 ((3U 
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
        bufp->chgBit(oldp+32,((0U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)));
        bufp->chgBit(oldp+33,(vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow));
        bufp->chgQData(oldp+34,(((QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp)) 
                                 * (QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))),64);
        bufp->chgCData(oldp+36,((0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                          >> 0x14U))),5);
        bufp->chgIData(oldp+37,((0x3fffffffU & (~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 2U)))),30);
        bufp->chgCData(oldp+38,(vlSelfRef.CoreTop__DOT__idu__DOT__decodedBundle_wbTarget),2);
        bufp->chgBit(oldp+39,((2U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd))));
        bufp->chgIData(oldp+40,(((0U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                  ? (((- (IData)(((0xffU 
                                                   == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                                  & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                     >> 7U)))) 
                                      << 8U) | (0xffU 
                                                & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                  : ((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                      ? (((- (IData)(
                                                     ((0xffU 
                                                       == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                                      & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                         >> 0xfU)))) 
                                          << 0x10U) 
                                         | (0xffffU 
                                            & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                      : vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))),32);
        bufp->chgIData(oldp+41,(vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata),32);
        bufp->chgBit(oldp+42,(((1U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd)) 
                               | (2U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd)))));
        bufp->chgCData(oldp+43,(((3U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                  ? 8U : ((2U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                           ? 4U : (
                                                   (1U 
                                                    == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                                    ? 2U
                                                    : 1U)))),8);
        bufp->chgIData(oldp+44,(vlSelfRef.CoreTop__DOT__lsu__DOT___dpicLSU_io_rdata),32);
        bufp->chgQData(oldp+45,((QData)((IData)(vlSelfRef.CoreTop__DOT___exu_io_out_aluOut))),64);
        bufp->chgQData(oldp+47,((QData)((IData)(vlSelfRef.CoreTop__DOT___regfile_io_rs2_data))),64);
        bufp->chgQData(oldp+49,((QData)((IData)((0xfffffffcU 
                                                 & vlSelfRef.CoreTop__DOT___exu_io_out_aluOut)))),64);
        bufp->chgIData(oldp+51,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
                                [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           >> 0x14U))]),32);
        bufp->chgIData(oldp+52,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
                                [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           >> 0xfU))]),32);
        bufp->chgIData(oldp+53,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[0]),32);
        bufp->chgIData(oldp+54,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[1]),32);
        bufp->chgIData(oldp+55,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[2]),32);
        bufp->chgIData(oldp+56,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[3]),32);
        bufp->chgIData(oldp+57,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[4]),32);
        bufp->chgIData(oldp+58,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[5]),32);
        bufp->chgIData(oldp+59,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[6]),32);
        bufp->chgIData(oldp+60,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[7]),32);
        bufp->chgIData(oldp+61,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[8]),32);
        bufp->chgIData(oldp+62,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[9]),32);
        bufp->chgIData(oldp+63,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[10]),32);
        bufp->chgIData(oldp+64,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[11]),32);
        bufp->chgIData(oldp+65,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[12]),32);
        bufp->chgIData(oldp+66,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[13]),32);
        bufp->chgIData(oldp+67,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[14]),32);
        bufp->chgIData(oldp+68,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[15]),32);
        bufp->chgIData(oldp+69,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[16]),32);
        bufp->chgIData(oldp+70,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[17]),32);
        bufp->chgIData(oldp+71,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[18]),32);
        bufp->chgIData(oldp+72,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[19]),32);
        bufp->chgIData(oldp+73,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[20]),32);
        bufp->chgIData(oldp+74,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[21]),32);
        bufp->chgIData(oldp+75,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[22]),32);
        bufp->chgIData(oldp+76,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[23]),32);
        bufp->chgIData(oldp+77,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[24]),32);
        bufp->chgIData(oldp+78,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[25]),32);
        bufp->chgIData(oldp+79,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[26]),32);
        bufp->chgIData(oldp+80,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[27]),32);
        bufp->chgIData(oldp+81,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[28]),32);
        bufp->chgIData(oldp+82,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[29]),32);
        bufp->chgIData(oldp+83,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[30]),32);
        bufp->chgIData(oldp+84,(vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[31]),32);
    }
    bufp->chgBit(oldp+85,(vlSelfRef.clock));
    bufp->chgBit(oldp+86,(vlSelfRef.reset));
    bufp->chgIData(oldp+87,(vlSelfRef.io_commit_pc),32);
    bufp->chgIData(oldp+88,(vlSelfRef.io_commit_inst),32);
    bufp->chgBit(oldp+89,(vlSelfRef.io_commit_valid));
    bufp->chgBit(oldp+90,(vlSelfRef.io_commit_is_store));
    bufp->chgBit(oldp+91,(vlSelfRef.io_commit_halt));
    bufp->chgCData(oldp+92,(vlSelfRef.io_commit_rd),5);
    bufp->chgIData(oldp+93,(vlSelfRef.io_commit_wdata),32);
    bufp->chgBit(oldp+94,(vlSelfRef.io_commit_wen));
    bufp->chgSData(oldp+95,(vlSelfRef.io_commit_csr_waddr),12);
    bufp->chgIData(oldp+96,(vlSelfRef.io_commit_csr_wdata),32);
    bufp->chgBit(oldp+97,(vlSelfRef.io_commit_csr_wen));
    bufp->chgBit(oldp+98,(((IData)(vlSelfRef.io_commit_wen) 
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
