// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCoreTop.h for the primary calling header

#include "VCoreTop__pch.h"
#include "VCoreTop__Syms.h"
#include "VCoreTop___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VCoreTop___024root___dump_triggers__stl(VCoreTop___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void VCoreTop___024root___eval_triggers__stl(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___eval_triggers__stl\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.setBit(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VCoreTop___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

void VCoreTop___024unit____Vdpiimwrap_paddr_read_TOP____024unit(IData/*31:0*/ io_raddr, IData/*31:0*/ &paddr_read__Vfuncrtn);
void VCoreTop___024unit____Vdpiimwrap_pmem_read_TOP____024unit(QData/*63:0*/ raddr, CData/*7:0*/ io_len, QData/*63:0*/ &pmem_read__Vfuncrtn);

VL_ATTR_COLD void VCoreTop___024root___stl_sequent__TOP__0(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___stl_sequent__TOP__0\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.io_commit_pc = vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg;
    VCoreTop___024unit____Vdpiimwrap_paddr_read_TOP____024unit(vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg, vlSelfRef.__Vfunc_paddr_read__0__Vfuncout);
    vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
        = vlSelfRef.__Vfunc_paddr_read__0__Vfuncout;
    vlSelfRef.io_commit_rd = (0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                       >> 7U));
    vlSelfRef.CoreTop__DOT___regfile_io_rs2_data = 
        ((0U == (0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                          >> 0x14U))) ? 0U : vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
         [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                    >> 0x14U))]);
    vlSelfRef.CoreTop__DOT___regfile_io_rs1_data = 
        ((0U == (0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                          >> 0xfU))) ? 0U : vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
         [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                    >> 0xfU))]);
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_24 
        = (1U & ((IData)((0x5073U == (0x507fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                 | (IData)((0x6073U == (0x607fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_42 
        = (IData)((0x40000000U == (0xfe000000U & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_37 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                          >> 4U)) << 3U)) | (4U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 3U))) 
              | ((2U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                        >> 5U)) | (1U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                         >> 0xeU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_37 
        = (IData)((0x4000U == (0x7000U & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_40 
        = (IData)((0x6000U == (0x6000U & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_40 
        = (((((0x8000U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                          << 0xfU)) | (0x4000U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                  << 0xdU))) 
             | ((0x2000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                >> 2U)) << 0xdU)) | 
                (0x1000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                >> 3U)) << 0xcU)))) 
            | (((0x800U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                           << 7U)) | (0x400U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                << 5U))) 
               | ((0x200U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                 >> 6U)) << 9U)) | 
                  (0x100U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                             >> 4U))))) | ((((0x80U 
                                              & ((~ 
                                                  (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 0xdU)) 
                                                 << 7U)) 
                                             | (0x40U 
                                                & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 8U))) 
                                            | ((0x20U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 0x19U)) 
                                                   << 5U)) 
                                               | (0x10U 
                                                  & ((~ 
                                                      (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                       >> 0x1aU)) 
                                                     << 4U)))) 
                                           | (((8U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 0x1bU)) 
                                                   << 3U)) 
                                               | (4U 
                                                  & ((~ 
                                                      (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                       >> 0x1cU)) 
                                                     << 2U))) 
                                              | ((2U 
                                                  & ((~ 
                                                      (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                       >> 0x1dU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (~ 
                                                       (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                        >> 0x1fU)))))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_33 
        = (IData)((0x2000U == (0x6000U & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_8 
        = (((0x20U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                      << 5U)) | ((0x10U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           << 3U)) 
                                 | (8U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                          << 1U)))) 
           | ((4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                         >> 3U)) << 2U)) | ((2U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 3U)) 
                                            | (1U & 
                                               (~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 6U))))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                          >> 5U)) << 3U)) | (4U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 6U)) 
                                                   << 2U))) 
              | ((2U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                            >> 0xcU)) << 1U)) | (1U 
                                                 & (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 0xdU))))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_30 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                      >> 1U)) | (4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           >> 5U)) 
                                       << 2U))) | (
                                                   (2U 
                                                    & ((~ 
                                                        (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                         >> 6U)) 
                                                       << 1U)) 
                                                   | (1U 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                         >> 0xdU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20 
        = ((((0x200U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                        << 9U)) | ((0x100U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                              << 7U)) 
                                   | (0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                               << 5U)))) 
            | ((0x40U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                             >> 3U)) << 6U)) | (0x20U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 4U)) 
                                                   << 5U)))) 
           | (((0x10U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                         >> 1U)) | ((8U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           >> 3U)) 
                                    | (4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                 >> 0xcU)) 
                                             << 2U)))) 
              | ((2U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                            >> 0xdU)) << 1U)) | (1U 
                                                 & (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 0xeU))))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                          >> 4U)) << 3U)) | (4U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 5U)) 
                                                   << 2U))) 
              | ((2U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                            >> 6U)) << 1U)) | (1U & 
                                               (~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 0xdU))))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_29 
        = (IData)((0U == (0x6000U & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21 
        = ((((0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                       << 6U)) | (0x20U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                           << 4U))) 
            | ((0x10U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                         << 2U)) | (8U & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
           | ((4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                         >> 4U)) << 2U)) | ((2U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 4U)) 
                                            | (1U & 
                                               (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                >> 6U)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_47 
        = ((4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                      >> 6U)) << 2U)) | ((2U & ((~ 
                                                 (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                  >> 0xcU)) 
                                                << 1U)) 
                                         | (1U & (~ 
                                                  (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 0xeU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_34 
        = (IData)((0U == (0xfc000000U & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_43 
        = ((vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
            >> 0xcU) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_29));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_30 
        = ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
               >> 6U)) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_29));
    vlSelfRef.CoreTop__DOT___idu_io_out_bits_src1Sel 
        = ((((IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_24) 
             | (0x37U == (0x7fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
            << 1U) | ((IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_24) 
                      | (((0x17U == (0x7fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                          | (0x3ffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20))) 
                         | (0x7fU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_10 
        = ((((0x100U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                        << 8U)) | ((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                             << 6U)) 
                                   | (0x40U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                   >> 2U)) 
                                               << 6U)))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                             >> 3U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 4U)) 
                                                   << 4U)))) 
           | ((8U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                     >> 2U)) | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_47)));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_48 
        = ((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                      >> 5U)) << 3U)) | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_47));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_35 
        = ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
               >> 0x19U)) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_34));
    vlSelfRef.CoreTop__DOT___idu_io_out_bits_bruOp 
        = (((((IData)((0x3ffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20))) 
              << 1U) << 2U) | (4U & (((0x7fU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)) 
                                      | (IData)(((0x63U 
                                                  == 
                                                  (0x7fU 
                                                   & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                 & ((IData)(
                                                            (0x5000U 
                                                             == 
                                                             (0x5000U 
                                                              & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                    | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_40))))) 
                                     << 2U))) | (((
                                                   (0x7fU 
                                                    == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)) 
                                                   | (IData)(
                                                             ((0x63U 
                                                               == 
                                                               (0x7fU 
                                                                & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                              & ((IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_43) 
                                                                 | ((IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_37) 
                                                                    | ((vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                                        >> 0xcU) 
                                                                       & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_40))))))) 
                                                  << 1U) 
                                                 | (1U 
                                                    & ((IData)(
                                                               (0x63U 
                                                                == 
                                                                (0x307fU 
                                                                 & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                       | ((0x7fU 
                                                           == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)) 
                                                          | (IData)(
                                                                    (0x4063U 
                                                                     == 
                                                                     (0x507fU 
                                                                      & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))))))));
    vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize 
        = (((IData)(((3U == (0x105fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                     & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_33))) 
            << 1U) | (1U & (IData)(((3U == (0x1fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                    & ((IData)((0x1000U 
                                                == 
                                                (0x3060U 
                                                 & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                       | ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                              >> 6U)) 
                                          & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_43)))))));
    vlSelfRef.CoreTop__DOT___idu_io_out_bits_src2Sel 
        = ((((0x3ffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20)) 
             | (0x7fU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21))) 
            << 1U) | (1U & ((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                            | ((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1)) 
                               | ((IData)((3U == (0x505fU 
                                                  & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                  | ((IData)(((3U == 
                                               (0x1fU 
                                                & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                              & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_30))) 
                                     | ((0x3fU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_8)) 
                                        | (0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_30)))))))));
    vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp = (
                                                   (0U 
                                                    == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_src1Sel))
                                                    ? vlSelfRef.CoreTop__DOT___regfile_io_rs1_data
                                                    : 
                                                   ((1U 
                                                     == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_src1Sel))
                                                     ? vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg
                                                     : 
                                                    ((2U 
                                                      == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_src1Sel))
                                                      ? 0U
                                                      : 
                                                     (0x1fU 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                         >> 0xfU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4 
        = (((0x100U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                       << 8U)) | ((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                            << 6U)) 
                                  | (0x40U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                  >> 2U)) 
                                              << 6U)))) 
           | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                            >> 3U)) << 5U)) | ((0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 4U)) 
                                                   << 4U)) 
                                               | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_48))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3 
        = (((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                      << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                          << 5U))) 
           | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                            >> 2U)) << 5U)) | ((0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                     >> 3U)) 
                                                   << 4U)) 
                                               | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_48))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_36 
        = ((~ (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
               >> 0xeU)) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_35));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_38 
        = ((vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
            >> 0xeU) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_35));
    vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSign 
        = ((0x1ffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
           | (IData)(((3U == (0x3fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                      & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_30))));
    vlSelfRef.CoreTop__DOT___exu_io_out_bits_memCmd 
        = ((((0x1ffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_10)) 
             | (IData)(((0x23U == (0x3fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                        & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_30)))) 
            << 1U) | ((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                      | (0x1ffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4))));
    vlSelfRef.CoreTop__DOT___lsu_io_out_bits_wbTarget 
        = ((2U & (((IData)((0x1073U == (0x107fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                   | (IData)((0x2073U == (0x207fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)))) 
                  << 1U)) | (1U & ((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                   | ((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1)) 
                                      | ((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3)) 
                                         | ((IData)(
                                                    ((0xfU 
                                                      == 
                                                      (0x107fU 
                                                       & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                     & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_29))) 
                                            | ((0x3fU 
                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_8)) 
                                               | ((IData)(
                                                          (0x33U 
                                                           == 
                                                           (0xbe00707fU 
                                                            & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                  | ((IData)(
                                                             ((0x33U 
                                                               == 
                                                               (0x7fU 
                                                                & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                              & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_34))) 
                                                     | ((0x3ffU 
                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20)) 
                                                        | ((0x7fU 
                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)) 
                                                           | ((IData)(
                                                                      (0x1073U 
                                                                       == 
                                                                       (0x107fU 
                                                                        & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                              | ((0xffU 
                                                                  == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_30)) 
                                                                 | ((IData)(
                                                                            (0x2073U 
                                                                             == 
                                                                             (0x207fU 
                                                                              & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                    | (0xffffU 
                                                                       == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_40))))))))))))))));
    vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp = (
                                                   ((0x3fU 
                                                     == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_8)) 
                                                    | (0x7fU 
                                                       == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)))
                                                    ? 
                                                   ((1U 
                                                     & ((0x1ffU 
                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_10)) 
                                                        | ((IData)(
                                                                   (0x23U 
                                                                    == 
                                                                    (0x603fU 
                                                                     & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                           | (0xffU 
                                                              == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_37)))))
                                                     ? 
                                                    ((1U 
                                                      & ((0xffU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                                         | ((0xffU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1)) 
                                                            | ((0xffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3)) 
                                                               | ((IData)(
                                                                          (0x41U 
                                                                           == 
                                                                           (0xffefffc1U 
                                                                            & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                  | ((IData)(
                                                                             (0x63U 
                                                                              == 
                                                                              (0x207fU 
                                                                               & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                     | ((IData)(
                                                                                (0x63U 
                                                                                == 
                                                                                (0x707bU 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                        | ((0x7fU 
                                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)) 
                                                                           | ((0xffU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_30)) 
                                                                              | (0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_37)))))))))))
                                                      ? 
                                                     (0x1fU 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                         >> 0x14U))
                                                      : 
                                                     (0x3fU 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                         >> 0x14U)))
                                                     : 
                                                    ((1U 
                                                      & ((0xffU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                                         | ((0xffU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1)) 
                                                            | ((0xffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3)) 
                                                               | ((IData)(
                                                                          (0x41U 
                                                                           == 
                                                                           (0xffefffc1U 
                                                                            & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                  | ((IData)(
                                                                             (0x63U 
                                                                              == 
                                                                              (0x207fU 
                                                                               & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                     | ((IData)(
                                                                                (0x63U 
                                                                                == 
                                                                                (0x707bU 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                        | ((0x7fU 
                                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)) 
                                                                           | ((0xffU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_30)) 
                                                                              | (0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_37)))))))))))
                                                      ? 
                                                     (((- (IData)(
                                                                  (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                                   >> 0x1fU))) 
                                                       << 0x14U) 
                                                      | (((0xff000U 
                                                           & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst) 
                                                          | (0x800U 
                                                             & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                                >> 9U))) 
                                                         | (0x7feU 
                                                            & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                               >> 0x14U))))
                                                      : 
                                                     (0xfffff000U 
                                                      & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)))
                                                    : 
                                                   ((1U 
                                                     & ((0x1ffU 
                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_10)) 
                                                        | ((IData)(
                                                                   (0x23U 
                                                                    == 
                                                                    (0x603fU 
                                                                     & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                           | (0xffU 
                                                              == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_37)))))
                                                     ? 
                                                    ((1U 
                                                      & ((0xffU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                                         | ((0xffU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1)) 
                                                            | ((0xffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3)) 
                                                               | ((IData)(
                                                                          (0x41U 
                                                                           == 
                                                                           (0xffefffc1U 
                                                                            & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                  | ((IData)(
                                                                             (0x63U 
                                                                              == 
                                                                              (0x207fU 
                                                                               & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                     | ((IData)(
                                                                                (0x63U 
                                                                                == 
                                                                                (0x707bU 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                        | ((0x7fU 
                                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)) 
                                                                           | ((0xffU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_30)) 
                                                                              | (0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_37)))))))))))
                                                      ? 
                                                     (((- (IData)(
                                                                  (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                                   >> 0x1fU))) 
                                                       << 0xcU) 
                                                      | ((0x800U 
                                                          & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                             << 4U)) 
                                                         | ((0x7e0U 
                                                             & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                                >> 0x14U)) 
                                                            | (0x1eU 
                                                               & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                                  >> 7U)))))
                                                      : 
                                                     (((- (IData)(
                                                                  (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                                   >> 0x1fU))) 
                                                       << 0xcU) 
                                                      | ((0xfe0U 
                                                          & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                             >> 0x14U)) 
                                                         | (0x1fU 
                                                            & (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                               >> 7U)))))
                                                     : 
                                                    ((1U 
                                                      & ((0xffU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                                         | ((0xffU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1)) 
                                                            | ((0xffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3)) 
                                                               | ((IData)(
                                                                          (0x41U 
                                                                           == 
                                                                           (0xffefffc1U 
                                                                            & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                  | ((IData)(
                                                                             (0x63U 
                                                                              == 
                                                                              (0x207fU 
                                                                               & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                     | ((IData)(
                                                                                (0x63U 
                                                                                == 
                                                                                (0x707bU 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst))) 
                                                                        | ((0x7fU 
                                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21)) 
                                                                           | ((0xffU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_30)) 
                                                                              | (0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_37)))))))))))
                                                      ? 
                                                     (((- (IData)(
                                                                  (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                                   >> 0x1fU))) 
                                                       << 0xcU) 
                                                      | (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                         >> 0x14U))
                                                      : 0U)));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_41 
        = ((vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
            >> 0xdU) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_38));
    vlSelfRef.io_commit_wen = (1U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_bits_wbTarget));
    vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT____VdfgRegularize_hfa6af0cb_0_0 
        = (vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp 
           + vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg);
    vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0 = 
        ((0U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_src2Sel))
          ? vlSelfRef.CoreTop__DOT___regfile_io_rs2_data
          : ((1U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_src2Sel))
              ? vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp
              : ((2U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_src2Sel))
                  ? 4U : 0U)));
    vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp 
        = ((((IData)(((0x13U == (0x1fU & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                      & ((IData)(((0U == (0x60U & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                  & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_33))) 
                         | (IData)(((0x2020U == (0x2060U 
                                                 & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                    & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_36)))))) 
             << 3U) | (((IData)(((0x1033U == (0x307fU 
                                              & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                 & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_35))) 
                        | ((IData)(((0x13U == (0x7fU 
                                               & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                    & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_37))) 
                           | ((IData)(((0x33U == (0x207fU 
                                                  & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                       & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_38))) 
                              | (0xffffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_40))))) 
                       << 2U)) | ((((0xffffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_40)) 
                                    | (IData)(((0x13U 
                                                == 
                                                (0x1fU 
                                                 & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                               & ((IData)(
                                                          ((0U 
                                                            == 
                                                            (0x60U 
                                                             & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                           & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_40))) 
                                                  | (IData)(
                                                            ((0x20U 
                                                              == 
                                                              (0x60U 
                                                               & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                             & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_41))))))) 
                                   << 1U) | (IData)(
                                                    ((0x13U 
                                                      == 
                                                      (0x1fU 
                                                       & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                     & ((IData)(
                                                                ((0x1020U 
                                                                  == 
                                                                  (0x1060U 
                                                                   & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                                 & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_36))) 
                                                        | ((IData)(
                                                                   ((0x1000U 
                                                                     == 
                                                                     (0x1060U 
                                                                      & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                                    & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_33))) 
                                                           | ((IData)(
                                                                      ((0U 
                                                                        == 
                                                                        (0x1060U 
                                                                         & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                                       & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_40))) 
                                                              | (IData)(
                                                                        ((0x20U 
                                                                          == 
                                                                          (0x60U 
                                                                           & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                                         & (((~ 
                                                                              (vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst 
                                                                               >> 0xcU)) 
                                                                             & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_41)) 
                                                                            | ((IData)(
                                                                                ((0U 
                                                                                == 
                                                                                (0x7000U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_42))) 
                                                                               | (IData)(
                                                                                ((0x5000U 
                                                                                == 
                                                                                (0x7000U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_nextStage_bits_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_42))))))))))))));
    vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp 
        = ((8U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
            ? ((4U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                ? 0U : ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                         ? ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                             ? 0U : vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp)
                         : ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                             ? (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                                < vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                             : VL_LTS_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))))
            : ((4U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                ? ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                    ? ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                        ? VL_SHIFTRS_III(32,32,32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, 
                                         (0x1fU & vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, 
                                        (0x1fU & vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))
                    : ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                        ? (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           << (0x1fU & vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                        : (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           ^ vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))
                : ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                    ? ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                        ? (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           | vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                        : (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           & vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                    : ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bits_aluOp))
                        ? (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           - vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                        : (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           + vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))));
    vlSelfRef.CoreTop__DOT__lsu__DOT___dpicLSU_io_rdata 
        = ((((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memCmd)) 
             | (2U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memCmd))) 
            & (2U != (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memCmd)))
            ? (IData)(([&]() {
                    VCoreTop___024unit____Vdpiimwrap_pmem_read_TOP____024unit((QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp)), 
                                                                              ((3U 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                                                                ? 8U
                                                                                : 
                                                                               ((2U 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                                                                 ? 4U
                                                                                 : 
                                                                                ((1U 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                                                                 ? 2U
                                                                                 : 1U))), vlSelfRef.__Vfunc_pmem_read__1__Vfuncout);
                }(), vlSelfRef.__Vfunc_pmem_read__1__Vfuncout))
            : 0U);
    vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
        = VL_SHIFTR_III(32,32,6, vlSelfRef.CoreTop__DOT__lsu__DOT___dpicLSU_io_rdata, 
                        (((3U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize)) 
                          | (2U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize)))
                          ? 0U : ((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                   ? (0x10U & (vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp 
                                               << 3U))
                                   : (0x18U & (vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp 
                                               << 3U)))));
    vlSelfRef.io_commit_wdata = ((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memCmd))
                                  ? ((0U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                      ? (((- (IData)(
                                                     ((IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSign) 
                                                      & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                         >> 7U)))) 
                                          << 8U) | 
                                         (0xffU & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                      : ((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSize))
                                          ? (((- (IData)(
                                                         ((IData)(vlSelfRef.CoreTop__DOT___exu_io_out_bits_memSign) 
                                                          & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                             >> 0xfU)))) 
                                              << 0x10U) 
                                             | (0xffffU 
                                                & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                          : vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                  : vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp);
}
