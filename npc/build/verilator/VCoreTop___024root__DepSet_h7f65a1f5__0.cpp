// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCoreTop.h for the primary calling header

#include "VCoreTop__pch.h"
#include "VCoreTop__Syms.h"
#include "VCoreTop___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VCoreTop___024root___dump_triggers__act(VCoreTop___024root* vlSelf);
#endif  // VL_DEBUG

void VCoreTop___024root___eval_triggers__act(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___eval_triggers__act\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VCoreTop___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void VCoreTop___024unit____Vdpiimwrap_npc_ebreak_TOP____024unit();
void VCoreTop___024unit____Vdpiimwrap_pmem_write_TOP____024unit(QData/*63:0*/ waddr, QData/*63:0*/ io_wdata, CData/*7:0*/ io_len);
void VCoreTop___024unit____Vdpiimwrap_paddr_read_TOP____024unit(IData/*31:0*/ io_raddr, IData/*31:0*/ &paddr_read__Vfuncrtn);
void VCoreTop___024unit____Vdpiimwrap_pmem_read_TOP____024unit(QData/*63:0*/ raddr, CData/*7:0*/ io_len, QData/*63:0*/ &pmem_read__Vfuncrtn);

VL_INLINE_OPT void VCoreTop___024root___nba_sequent__TOP__0(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___nba_sequent__TOP__0\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __Vdly__CoreTop__DOT__ifu__DOT__pcReg;
    __Vdly__CoreTop__DOT__ifu__DOT__pcReg = 0;
    IData/*31:0*/ __VdlyVal__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0;
    __VdlyVal__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0 = 0;
    CData/*4:0*/ __VdlyDim0__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0;
    __VdlyDim0__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0 = 0;
    CData/*0:0*/ __VdlySet__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0;
    __VdlySet__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0 = 0;
    // Body
    if (vlSelfRef.io_commit_halt) {
        VCoreTop___024unit____Vdpiimwrap_npc_ebreak_TOP____024unit();
    }
    if ((((1U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd)) 
          | (2U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd))) 
         & (2U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd)))) {
        VCoreTop___024unit____Vdpiimwrap_pmem_write_TOP____024unit((QData)((IData)(vlSelfRef.CoreTop__DOT___exu_io_out_aluOut)), (QData)((IData)(vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)), 
                                                                   ((3U 
                                                                     == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                                                     ? 8U
                                                                     : 
                                                                    ((2U 
                                                                      == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                                                      ? 4U
                                                                      : 
                                                                     ((1U 
                                                                       == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                                                       ? 2U
                                                                       : 1U))));
    }
    __VdlySet__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0 = 0U;
    __Vdly__CoreTop__DOT__ifu__DOT__pcReg = vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg;
    if (((IData)(vlSelfRef.io_commit_wen) & (0U != (IData)(vlSelfRef.io_commit_rd)))) {
        __VdlyVal__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0 
            = vlSelfRef.io_commit_wdata;
        __VdlyDim0__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0 
            = vlSelfRef.io_commit_rd;
        __VdlySet__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0 = 1U;
    }
    if (vlSelfRef.reset) {
        __Vdly__CoreTop__DOT__ifu__DOT__pcReg = 0x80000000U;
        vlSelfRef.CoreTop__DOT__csrfile__DOT__mstatus = 0U;
        vlSelfRef.CoreTop__DOT__csrfile__DOT__mtvec = 0U;
        vlSelfRef.CoreTop__DOT__csrfile__DOT__mcause = 0U;
        vlSelfRef.CoreTop__DOT__csrfile__DOT__mepc = 0U;
    } else {
        __Vdly__CoreTop__DOT__ifu__DOT__pcReg = (((1U 
                                                   == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                   ? 
                                                  (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                                   == vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                   : 
                                                  ((2U 
                                                    == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                    ? 
                                                   (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                                    != vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                    : 
                                                   ((3U 
                                                     == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                     ? 
                                                    VL_LTS_III(32, vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data, vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                     : 
                                                    ((4U 
                                                      == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                      ? 
                                                     VL_GTES_III(32, vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data, vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                      : 
                                                     ((5U 
                                                       == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                       ? 
                                                      (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                                       < vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                       : 
                                                      ((6U 
                                                        == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                                                        ? 
                                                       (vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
                                                        >= vlSelfRef.CoreTop__DOT___regfile_io_rs2_data)
                                                        : 
                                                       ((7U 
                                                         == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp)) 
                                                        | ((8U 
                                                            == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp)) 
                                                           | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_4)))))))))
                                                  ? vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT__casez_tmp
                                                  : 
                                                 ((IData)(4U) 
                                                  + vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg));
        if ((1U & (~ ((0x73U == vlSelfRef.CoreTop__DOT___ifu_io_sc_inst) 
                      | (~ ((IData)(vlSelfRef.io_commit_csr_wen) 
                            & (0x300U == (IData)(vlSelfRef.io_commit_csr_waddr)))))))) {
            vlSelfRef.CoreTop__DOT__csrfile__DOT__mstatus 
                = vlSelfRef.CoreTop__DOT__csrfile__DOT__new_val;
        }
        if ((1U & (~ ((0x73U == vlSelfRef.CoreTop__DOT___ifu_io_sc_inst) 
                      | (~ ((IData)(vlSelfRef.io_commit_csr_wen) 
                            & (0x305U == (IData)(vlSelfRef.io_commit_csr_waddr)))))))) {
            vlSelfRef.CoreTop__DOT__csrfile__DOT__mtvec 
                = vlSelfRef.CoreTop__DOT__csrfile__DOT__new_val;
        }
        if ((0x73U == vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) {
            vlSelfRef.CoreTop__DOT__csrfile__DOT__mcause = 0xbU;
            vlSelfRef.CoreTop__DOT__csrfile__DOT__mepc 
                = vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg;
        } else {
            if (((IData)(vlSelfRef.io_commit_csr_wen) 
                 & (0x342U == (IData)(vlSelfRef.io_commit_csr_waddr)))) {
                vlSelfRef.CoreTop__DOT__csrfile__DOT__mcause 
                    = vlSelfRef.CoreTop__DOT__csrfile__DOT__new_val;
            }
            if (((IData)(vlSelfRef.io_commit_csr_wen) 
                 & (0x341U == (IData)(vlSelfRef.io_commit_csr_waddr)))) {
                vlSelfRef.CoreTop__DOT__csrfile__DOT__mepc 
                    = vlSelfRef.CoreTop__DOT__csrfile__DOT__new_val;
            }
        }
    }
    if (__VdlySet__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0) {
        vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[__VdlyDim0__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0] 
            = __VdlyVal__CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory__v0;
    }
    vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg = __Vdly__CoreTop__DOT__ifu__DOT__pcReg;
    vlSelfRef.io_commit_pc = vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg;
    VCoreTop___024unit____Vdpiimwrap_paddr_read_TOP____024unit(vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg, vlSelfRef.__Vfunc_paddr_read__0__Vfuncout);
    vlSelfRef.CoreTop__DOT___ifu_io_sc_inst = vlSelfRef.__Vfunc_paddr_read__0__Vfuncout;
    vlSelfRef.io_commit_inst = vlSelfRef.CoreTop__DOT___ifu_io_sc_inst;
    vlSelfRef.io_commit_halt = (0x100073U == vlSelfRef.CoreTop__DOT___ifu_io_sc_inst);
    vlSelfRef.io_commit_rd = (0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 7U));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_72 
        = (IData)((0x4000U == (0x7000U & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_74 
        = (IData)((0x6000U == (0x6000U & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_33 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      >> 1U)) | (4U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 3U))) | (
                                                   (2U 
                                                    & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                       >> 5U)) 
                                                   | (1U 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                         >> 0xcU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_39 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      >> 1U)) | (4U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 3U))) | (
                                                   (2U 
                                                    & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                       >> 5U)) 
                                                   | (1U 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                         >> 0xdU)))));
    vlSelfRef.CoreTop__DOT___regfile_io_rs2_data = 
        ((0U == (0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          >> 0x14U))) ? 0U : vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
         [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                    >> 0x14U))]);
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_68 
        = (IData)((0x2000U == (0x6000U & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_66 
        = (1U & ((IData)((0x5073U == (0x507fU & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                 | (IData)((0x6073U == (0x607fU & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_76 
        = (IData)((0x40000000U == (0xfc000000U & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)));
    vlSelfRef.CoreTop__DOT___regfile_io_rs1_data = 
        ((0U == (0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          >> 0xfU))) ? 0U : vlSelfRef.CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory
         [(0x1fU & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                    >> 0xfU))]);
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          >> 4U)) << 3U)) | (4U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 3U))) 
              | ((2U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        >> 5U)) | (1U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                         >> 0xeU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_15 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          >> 4U)) << 3U)) | (4U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 3U))) 
              | ((2U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        >> 5U)) | (1U & (~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                            >> 0xdU))))));
    vlSelfRef.io_commit_csr_waddr = ((0x73U == vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)
                                      ? 0x305U : ((0x30200073U 
                                                   == vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)
                                                   ? 0x341U
                                                   : 
                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 0x14U)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_7 
        = (((0x20U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      << 5U)) | ((0x10U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 3U)) 
                                 | (8U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                          << 1U)))) 
           | ((4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 3U)) << 2U)) | ((2U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 3U)) 
                                            | (1U & 
                                               (~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 6U))))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_36 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      >> 1U)) | (4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           >> 5U)) 
                                       << 2U))) | (
                                                   (2U 
                                                    & ((~ 
                                                        (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                         >> 6U)) 
                                                       << 1U)) 
                                                   | (1U 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                         >> 0xdU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | (((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          >> 4U)) << 3U)) | (4U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 5U)) 
                                                   << 2U))) 
              | ((2U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                            >> 6U)) << 1U)) | (1U & 
                                               (~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 0xdU))))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_81 
        = ((4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      >> 5U)) << 2U)) | ((2U & ((~ 
                                                 (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  >> 6U)) 
                                                << 1U)) 
                                         | (1U & (~ 
                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 0xcU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_53 
        = (IData)((0U == (0xfc000000U & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19 
        = ((((0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 6U)) | (0x20U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 4U))) 
            | ((0x10U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         << 2U)) | (8U & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
           | ((4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 4U)) << 2U)) | ((2U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 4U)) 
                                            | (1U & 
                                               (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                >> 6U)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_82 
        = ((2U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      >> 6U)) << 1U)) | (1U & (~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  >> 0xeU))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_83 
        = ((4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      >> 0xcU)) << 2U)) | ((2U & ((~ 
                                                   (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                    >> 0xdU)) 
                                                  << 1U)) 
                                           | (1U & 
                                              (~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  >> 0xeU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_92 
        = (((0x10U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          >> 0x1aU)) << 4U)) | ((8U 
                                                 & ((~ 
                                                     (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                      >> 0x1bU)) 
                                                    << 3U)) 
                                                | (4U 
                                                   & ((~ 
                                                       (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                        >> 0x1cU)) 
                                                      << 2U)))) 
           | ((2U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 0x1dU)) << 1U)) | (1U & 
                                               (~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 0x1fU)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_86 
        = ((2U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      >> 0x1eU)) << 1U)) | (1U & (~ 
                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 0x1fU))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_69 
        = ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
               >> 6U)) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_68));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_77 
        = ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
               >> 0x19U)) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_76));
    vlSelfRef.CoreTop__DOT___csrfile_io_csr_rdata = 
        ((0x342U == (IData)(vlSelfRef.io_commit_csr_waddr))
          ? vlSelfRef.CoreTop__DOT__csrfile__DOT__mcause
          : ((0x341U == (IData)(vlSelfRef.io_commit_csr_waddr))
              ? vlSelfRef.CoreTop__DOT__csrfile__DOT__mepc
              : ((0x305U == (IData)(vlSelfRef.io_commit_csr_waddr))
                  ? vlSelfRef.CoreTop__DOT__csrfile__DOT__mtvec
                  : ((0x300U == (IData)(vlSelfRef.io_commit_csr_waddr))
                      ? vlSelfRef.CoreTop__DOT__csrfile__DOT__mstatus
                      : 0U))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | ((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 4U)) << 3U)) | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_81)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T 
        = (((0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      << 6U)) | (0x20U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                          << 4U))) 
           | ((0x10U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                            >> 2U)) << 4U)) | ((8U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 3U)) 
                                               | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_81))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_79 
        = ((vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
            >> 0x19U) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_53));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_70 
        = ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
               >> 0x19U)) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_53));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_9 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | ((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 4U)) << 3U)) | ((4U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 3U)) 
                                            | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_82))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3 
        = ((((0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 6U)) | (0x20U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 4U))) 
            | ((0x10U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 4U)) | (8U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 3U)))) 
           | ((4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 4U)) << 2U)) | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_82)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4 
        = ((((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 7U)) | (0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 5U))) 
            | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 2U)) << 5U)) | (0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 3U)) 
                                                   << 4U)))) 
           | ((8U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 4U)) << 3U)) | ((4U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 5U)) 
                                                   << 2U)) 
                                            | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_82))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_84 
        = ((0x10U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 5U)) << 4U)) | ((8U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 6U)) 
                                                   << 3U)) 
                                            | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_83)));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_85 
        = (((0x40U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          >> 3U)) << 6U)) | (0x20U 
                                             & ((~ 
                                                 (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  >> 4U)) 
                                                << 5U))) 
           | ((0x10U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        >> 1U)) | ((8U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                          >> 3U)) | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_83))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_46 
        = (((((0x4000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          << 0xeU)) | (0x2000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  << 0xcU))) 
             | ((0x1000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                >> 2U)) << 0xcU)) | 
                (0x800U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                               >> 3U)) << 0xbU)))) 
            | (((0x400U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                           << 6U)) | (0x200U & ((~ 
                                                 (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  >> 5U)) 
                                                << 9U))) 
               | ((0x100U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                 >> 6U)) << 8U)) | 
                  (0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                            >> 5U))))) | ((0x40U & 
                                           ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                >> 0xdU)) 
                                            << 6U)) 
                                          | ((0x20U 
                                              & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 >> 9U)) 
                                             | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_92))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_93 
        = (((0x200U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                           >> 6U)) << 9U)) | ((0x100U 
                                               & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  >> 4U)) 
                                              | (0x80U 
                                                 & ((~ 
                                                     (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                      >> 0xdU)) 
                                                    << 7U)))) 
           | ((0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        >> 8U)) | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 >> 0x19U)) 
                                             << 5U)) 
                                   | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_92))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_68 
        = ((((((0x8000000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                              << 0x17U)) | (0x4000000U 
                                            & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                               << 0x15U))) 
              | ((0x2000000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                << 0x13U)) | (0x1000000U 
                                              & ((~ 
                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 7U)) 
                                                 << 0x18U)))) 
             | ((0x800000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                  >> 8U)) << 0x17U)) 
                | ((0x400000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                     >> 9U)) << 0x16U)) 
                   | (0x200000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 0xaU)) << 0x15U))))) 
            | ((((0x100000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0xbU)) << 0x14U)) 
                 | (0x80000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                    >> 0xcU)) << 0x13U))) 
                | ((0x40000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                    >> 0xdU)) << 0x12U)) 
                   | (0x20000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                      >> 0xeU)) << 0x11U)))) 
               | ((0x10000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0xfU)) << 0x10U)) 
                  | ((0x8000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                     >> 0x10U)) << 0xfU)) 
                     | (0x4000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 0x11U)) << 0xeU)))))) 
           | (((((0x2000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                 >> 0x12U)) << 0xdU)) 
                 | (0x1000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0x13U)) << 0xcU))) 
                | ((0x800U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                  >> 0x14U)) << 0xbU)) 
                   | (0x400U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                >> 0xbU)))) | ((0x200U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 0x16U)) 
                                                   << 9U)) 
                                               | ((0x100U 
                                                   & ((~ 
                                                       (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                        >> 0x17U)) 
                                                      << 8U)) 
                                                  | (0x80U 
                                                     & ((~ 
                                                         (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                          >> 0x18U)) 
                                                        << 7U))))) 
              | ((((0x40U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                 >> 0x19U)) << 6U)) 
                   | (0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0x1aU)) << 5U))) 
                  | ((0x10U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0x1bU)) << 4U)) 
                     | (8U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                              >> 0x19U)))) | ((4U & 
                                               (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                >> 0x1bU)) 
                                              | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_86)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_87 
        = ((4U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      >> 0x1dU)) << 2U)) | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_86));
    vlSelfRef.CoreTop__DOT___exu_io_out_memSize = (
                                                   (2U 
                                                    & ((IData)(
                                                               ((3U 
                                                                 == 
                                                                 (0x1fU 
                                                                  & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                & ((IData)(
                                                                           (0x2000U 
                                                                            == 
                                                                            (0x3060U 
                                                                             & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                                   | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_69)))) 
                                                       << 1U)) 
                                                   | (1U 
                                                      & (IData)(
                                                                ((3U 
                                                                  == 
                                                                  (0x1fU 
                                                                   & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                 & ((IData)(
                                                                            (0x1000U 
                                                                             == 
                                                                             (0x3060U 
                                                                              & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                                    | (IData)(
                                                                              (0x1000U 
                                                                               == 
                                                                               (0x5040U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))))))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_78 
        = (IData)(((0x5000U == (0x7040U & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                   & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_77)));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_80 
        = ((vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
            >> 0xeU) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_79));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_71 
        = ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
               >> 0xeU)) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_70));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_73 
        = ((vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
            >> 0xeU) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_70));
    vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd = (((IData)(
                                                           (0xffU 
                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_9))) 
                                                   << 1U) 
                                                  | ((0xffU 
                                                      == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1)) 
                                                     | ((0xffU 
                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2)) 
                                                        | (0xffU 
                                                           == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_5 
        = (((0x200U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 9U)) | ((0x100U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                             << 7U)) 
                                  | (0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                              << 5U)))) 
           | ((0x40U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        << 3U)) | ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 >> 4U)) 
                                             << 5U)) 
                                   | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_84))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_6 
        = (((0x100U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                       << 8U)) | (0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 6U))) 
           | ((0x40U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                            >> 2U)) << 6U)) | ((0x20U 
                                                & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   << 1U)) 
                                               | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_84))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_17 
        = ((0x100U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      << 8U)) | ((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                           << 6U)) 
                                 | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_85)));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_18 
        = ((0x200U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                      << 9U)) | ((0x100U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                            << 7U)) 
                                 | ((0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                              << 5U)) 
                                    | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_85))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_47 
        = (((0x4000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        << 0xeU)) | ((0x2000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 << 0xcU)) 
                                     | (0x1000U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 2U)) 
                                                   << 0xcU)))) 
           | ((0x800U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         << 8U)) | ((0x400U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                               << 6U)) 
                                    | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_93))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_49 
        = (((0x4000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        << 0xeU)) | ((0x2000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 << 0xcU)) 
                                     | (0x1000U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 2U)) 
                                                   << 0xcU)))) 
           | ((0x800U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         << 7U)) | ((0x400U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                               << 5U)) 
                                    | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_93))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48 
        = (((0x8000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        << 0xfU)) | ((0x4000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 << 0xdU)) 
                                     | (0x2000U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 2U)) 
                                                   << 0xdU)))) 
           | ((0x1000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          << 9U)) | ((0x800U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                << 7U)) 
                                     | ((0x400U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 5U)) 
                                                   << 0xaU)) 
                                        | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_93)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_67 
        = ((((((0x8000000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                              << 0x17U)) | (0x4000000U 
                                            & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                               << 0x15U))) 
              | ((0x2000000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                << 0x13U)) | (0x1000000U 
                                              & ((~ 
                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 7U)) 
                                                 << 0x18U)))) 
             | ((0x800000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                  >> 8U)) << 0x17U)) 
                | ((0x400000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                     >> 9U)) << 0x16U)) 
                   | (0x200000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 0xaU)) << 0x15U))))) 
            | ((((0x100000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0xbU)) << 0x14U)) 
                 | (0x80000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                    >> 0xcU)) << 0x13U))) 
                | ((0x40000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                    >> 0xdU)) << 0x12U)) 
                   | (0x20000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                      >> 0xeU)) << 0x11U)))) 
               | ((0x10000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0xfU)) << 0x10U)) 
                  | ((0x8000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                     >> 0x10U)) << 0xfU)) 
                     | (0x4000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 0x11U)) << 0xeU)))))) 
           | (((((0x2000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                 >> 0x12U)) << 0xdU)) 
                 | (0x1000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0x13U)) << 0xcU))) 
                | ((0x800U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                              >> 9U)) | (0x400U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 0x15U)) 
                                                   << 0xaU)))) 
               | ((0x200U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 0xdU)) | ((0x100U & 
                                           ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                >> 0x17U)) 
                                            << 8U)) 
                                          | (0x80U 
                                             & ((~ 
                                                 (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  >> 0x18U)) 
                                                << 7U))))) 
              | (((0x40U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                >> 0x19U)) << 6U)) 
                  | (0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                  >> 0x1aU)) << 5U))) 
                 | ((0x10U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                  >> 0x1bU)) << 4U)) 
                    | ((8U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                              >> 0x19U)) | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_87))))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_88 
        = ((0x20U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 0x1aU)) << 5U)) | ((0x10U 
                                                & ((~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 0x1bU)) 
                                                   << 4U)) 
                                               | ((8U 
                                                   & ((~ 
                                                       (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                        >> 0x1cU)) 
                                                      << 3U)) 
                                                  | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_87))));
    vlSelfRef.CoreTop__DOT___idu_io_out_mduOp = ((((IData)(
                                                           ((0x3033U 
                                                             == 
                                                             (0x307fU 
                                                              & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                            & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_80))) 
                                                   << 3U) 
                                                  | ((IData)(
                                                             ((0x33U 
                                                               == 
                                                               (0x7fU 
                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                              & ((IData)(
                                                                         ((0x3000U 
                                                                           == 
                                                                           (0x7000U 
                                                                            & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                          & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_79))) 
                                                                 | ((IData)(
                                                                            (0x3000U 
                                                                             != 
                                                                             (0x3000U 
                                                                              & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                                    & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_80))))) 
                                                     << 2U)) 
                                                 | (((IData)(
                                                             ((0x33U 
                                                               == 
                                                               (0x7fU 
                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                              & ((IData)(
                                                                         ((0x1000U 
                                                                           == 
                                                                           (0x3000U 
                                                                            & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                          & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_79))) 
                                                                 | (IData)(
                                                                           ((0x2000U 
                                                                             == 
                                                                             (0x3000U 
                                                                              & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                            & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_79)))))) 
                                                     << 1U) 
                                                    | (IData)(
                                                              ((0x33U 
                                                                == 
                                                                (0x107fU 
                                                                 & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                               & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_79)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_75 
        = ((vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
            >> 0xdU) & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_73));
    vlSelfRef.io_commit_is_store = (2U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_61 
        = ((0x7fffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_46)) 
           | ((0x7fffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_47)) 
              | (0x7fffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_49))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_44 
        = ((0xfffffffU == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_67) 
           | (0xfffffffU == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_68));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_25 
        = (((((0x4000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          << 0xeU)) | (0x2000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  << 0xcU))) 
             | ((0x1000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                >> 2U)) << 0xcU)) | 
                (0x800U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                               >> 3U)) << 0xbU)))) 
            | (((0x400U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                           << 6U)) | (0x200U & ((~ 
                                                 (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                  >> 5U)) 
                                                << 9U))) 
               | ((0x100U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                 >> 6U)) << 8U)) | 
                  (0x80U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                            >> 5U))))) | ((0x40U & 
                                           ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                >> 0xdU)) 
                                            << 6U)) 
                                          | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_88)));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_89 
        = ((0x40U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         >> 0x19U)) << 6U)) | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_88));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_90 
        = (((0x400U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                           >> 0x15U)) << 0xaU)) | (0x200U 
                                                   & ((~ 
                                                       (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                        >> 0x16U)) 
                                                      << 9U))) 
           | ((0x100U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                             >> 0x17U)) << 8U)) | (
                                                   (0x80U 
                                                    & ((~ 
                                                        (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                         >> 0x18U)) 
                                                       << 7U)) 
                                                   | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_89))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_91 
        = ((0x200U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          >> 6U)) << 9U)) | ((0x100U 
                                              & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 >> 4U)) 
                                             | ((0x80U 
                                                 & ((~ 
                                                     (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                      >> 0xdU)) 
                                                    << 7U)) 
                                                | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_89))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21 
        = ((((((0x8000000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                              << 0x1bU)) | (0x4000000U 
                                            & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                               << 0x16U))) 
              | ((0x2000000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                << 0x14U)) | (0x1000000U 
                                              & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 << 0x12U)))) 
             | ((0x800000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                  >> 7U)) << 0x17U)) 
                | ((0x400000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                     >> 8U)) << 0x16U)) 
                   | (0x200000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 9U)) << 0x15U))))) 
            | ((((0x100000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0xaU)) << 0x14U)) 
                 | (0x80000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                    >> 0xbU)) << 0x13U))) 
                | ((0x40000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                    >> 0xcU)) << 0x12U)) 
                   | (0x20000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                      >> 0xdU)) << 0x11U)))) 
               | ((0x10000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0xeU)) << 0x10U)) 
                  | ((0x8000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                     >> 0xfU)) << 0xfU)) 
                     | (0x4000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 0x10U)) << 0xeU)))))) 
           | ((0x2000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                              >> 0x11U)) << 0xdU)) 
              | ((0x1000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                 >> 0x12U)) << 0xcU)) 
                 | ((0x800U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0x13U)) << 0xbU)) 
                    | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_90)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20 
        = ((((((0x8000000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                              << 0x17U)) | (0x4000000U 
                                            & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                               << 0x15U))) 
              | ((0x2000000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                << 0x13U)) | (0x1000000U 
                                              & ((~ 
                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                   >> 7U)) 
                                                 << 0x18U)))) 
             | ((0x800000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                  >> 8U)) << 0x17U)) 
                | ((0x400000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                     >> 9U)) << 0x16U)) 
                   | (0x200000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 0xaU)) << 0x15U))))) 
            | ((((0x100000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0xbU)) << 0x14U)) 
                 | (0x80000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                    >> 0xcU)) << 0x13U))) 
                | ((0x40000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                    >> 0xdU)) << 0x12U)) 
                   | (0x20000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                      >> 0xeU)) << 0x11U)))) 
               | ((0x10000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0xfU)) << 0x10U)) 
                  | ((0x8000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                     >> 0x10U)) << 0xfU)) 
                     | (0x4000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                       >> 0x11U)) << 0xeU)))))) 
           | ((0x2000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                              >> 0x12U)) << 0xdU)) 
              | ((0x1000U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                 >> 0x13U)) << 0xcU)) 
                 | ((0x800U & ((~ (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                   >> 0x14U)) << 0xbU)) 
                    | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_90)))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_27 
        = (((0x4000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        << 0xeU)) | ((0x2000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 << 0xcU)) 
                                     | (0x1000U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 2U)) 
                                                   << 0xcU)))) 
           | ((0x800U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                         << 8U)) | ((0x400U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                               << 6U)) 
                                    | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_91))));
    vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28 
        = (((0x8000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                        << 0xfU)) | ((0x4000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                 << 0xdU)) 
                                     | (0x2000U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 2U)) 
                                                   << 0xdU)))) 
           | ((0x1000U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                          << 9U)) | ((0x800U & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                << 7U)) 
                                     | ((0x400U & (
                                                   (~ 
                                                    (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                     >> 5U)) 
                                                   << 0xaU)) 
                                        | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_91)))));
    vlSelfRef.CoreTop__DOT___idu_io_out_fuType = ((
                                                   ((0x3ffU 
                                                     == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_5)) 
                                                    | ((0xfffffffU 
                                                        == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21) 
                                                       | ((0xffU 
                                                           == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_33)) 
                                                          | ((0xffU 
                                                              == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_39)) 
                                                             | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_44))))) 
                                                   << 2U) 
                                                  | ((((0xffU 
                                                        == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1)) 
                                                       | ((0xffU 
                                                           == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2)) 
                                                          | ((0x7fU 
                                                              == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3)) 
                                                             | ((0x3ffU 
                                                                 == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_5)) 
                                                                | (IData)(
                                                                          ((0x2000033U 
                                                                            == 
                                                                            (0x200007fU 
                                                                             & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                           & (0x3fU 
                                                                              == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_88)))))))) 
                                                      << 1U) 
                                                     | ((0xffU 
                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_15)) 
                                                        | ((0x1ffU 
                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_17)) 
                                                           | ((0x7fU 
                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                              | ((0xffU 
                                                                  == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43)) 
                                                                 | (IData)(
                                                                           ((0x2000033U 
                                                                             == 
                                                                             (0x200007fU 
                                                                              & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                            & (0x3fU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_88))))))))));
    vlSelfRef.CoreTop__DOT___wbu_io_csr_op = ((((0xfffffffU 
                                                 == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21) 
                                                | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_44)) 
                                               << 2U) 
                                              | ((((0xffU 
                                                    == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_39)) 
                                                   | (0xfffffffU 
                                                      == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_68)) 
                                                  << 1U) 
                                                 | ((0xfffffffU 
                                                     == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20) 
                                                    | (0xffU 
                                                       == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_33)))));
    vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_65 
        = ((0xfffffffU == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20) 
           | (0xfffffffU == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_68));
    vlSelfRef.CoreTop__DOT__idu__DOT__decodedBundle_wbTarget 
        = ((((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_33)) 
             | (0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_39))) 
            << 1U) | (1U & ((0x7fU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                            | ((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2)) 
                               | ((0xffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                  | ((0x3ffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_5)) 
                                     | ((0x1ffU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_6)) 
                                        | ((0x3fU == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_7)) 
                                           | ((IData)(
                                                      (0x33U 
                                                       == 
                                                       (0xbe007077U 
                                                        & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                              | ((IData)(
                                                         ((0x33U 
                                                           == 
                                                           (0x7fU 
                                                            & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                          & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_53))) 
                                                 | ((0x3ffU 
                                                     == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_18)) 
                                                    | ((0x7fU 
                                                        == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                       | ((IData)(
                                                                  ((0x1013U 
                                                                    == 
                                                                    (0x305fU 
                                                                     & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                   & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_53))) 
                                                          | ((0x7fffU 
                                                              == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_27)) 
                                                             | ((0xffU 
                                                                 == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_33)) 
                                                                | ((0xffU 
                                                                    == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_36)) 
                                                                   | ((0xffU 
                                                                       == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_39)) 
                                                                      | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_61))))))))))))))))));
    vlSelfRef.CoreTop__DOT___idu_io_out_aluOp = ((((IData)(
                                                           ((0x13U 
                                                             == 
                                                             (0x1fU 
                                                              & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                            & (((~ 
                                                                 (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                                  >> 5U)) 
                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_69)) 
                                                               | (IData)(
                                                                         ((0x2020U 
                                                                           == 
                                                                           (0x2060U 
                                                                            & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                          & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_71)))))) 
                                                   << 3U) 
                                                  | (((0x7fffU 
                                                       == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_25)) 
                                                      | ((0x7fffU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_27)) 
                                                         | ((IData)(
                                                                    ((0x1033U 
                                                                      == 
                                                                      (0x3077U 
                                                                       & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                     & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_70))) 
                                                            | ((IData)(
                                                                       ((0x13U 
                                                                         == 
                                                                         (0x7fU 
                                                                          & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                        & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_72))) 
                                                               | ((IData)(
                                                                          ((0x33U 
                                                                            == 
                                                                            (0x207fU 
                                                                             & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                           & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_73))) 
                                                                  | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_61)))))) 
                                                     << 2U)) 
                                                 | ((((0x7fffU 
                                                       == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_46)) 
                                                      | ((0x7fffU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_47)) 
                                                         | ((0x7fffU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_49)) 
                                                            | (IData)(
                                                                      ((0x13U 
                                                                        == 
                                                                        (0x1fU 
                                                                         & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                       & ((IData)(
                                                                                ((0U 
                                                                                == 
                                                                                (0x60U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_74))) 
                                                                          | (IData)(
                                                                                ((0x20U 
                                                                                == 
                                                                                (0x60U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_75))))))))) 
                                                     << 1U) 
                                                    | (IData)(
                                                              ((3U 
                                                                == 
                                                                (7U 
                                                                 & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                               & ((IData)(
                                                                          ((0x1010U 
                                                                            == 
                                                                            (0x7078U 
                                                                             & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                           & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_53))) 
                                                                  | ((IData)(
                                                                             ((0x1018U 
                                                                               == 
                                                                               (0x3058U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                              & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_71))) 
                                                                     | ((IData)(
                                                                                ((0x1030U 
                                                                                == 
                                                                                (0x1078U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_71))) 
                                                                        | ((IData)(
                                                                                ((0x1010U 
                                                                                == 
                                                                                (0x1078U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_68))) 
                                                                           | ((IData)(
                                                                                ((0x10U 
                                                                                == 
                                                                                (0x1078U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_74))) 
                                                                              | ((IData)(
                                                                                ((0x30U 
                                                                                == 
                                                                                (0x1078U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_75))) 
                                                                                | ((IData)(
                                                                                ((0x30U 
                                                                                == 
                                                                                (0x7070U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_77))) 
                                                                                | ((IData)(
                                                                                ((0x5010U 
                                                                                == 
                                                                                (0x7078U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_76))) 
                                                                                | ((IData)(
                                                                                ((0x18U 
                                                                                == 
                                                                                (0x18U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_78))) 
                                                                                | (IData)(
                                                                                ((0x30U 
                                                                                == 
                                                                                (0x30U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                                & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_78))))))))))))))));
    vlSelfRef.CoreTop__DOT___idu_io_out_src2Sel = (
                                                   (((0x3ffU 
                                                      == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_18)) 
                                                     | (0x7fU 
                                                        == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19))) 
                                                    << 1U) 
                                                   | ((0x7fU 
                                                       == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                                      | ((0xffU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2)) 
                                                         | ((0x7fU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3)) 
                                                            | ((0x1ffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_6)) 
                                                               | ((0x3fU 
                                                                   == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_7)) 
                                                                  | ((0x7fffU 
                                                                      == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_25)) 
                                                                     | ((0xffffU 
                                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28)) 
                                                                        | ((0xffU 
                                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_36)) 
                                                                           | ((0x7fffU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_46)) 
                                                                              | (0xffffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48))))))))))));
    vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp = (
                                                   ((0x3fU 
                                                     == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_7)) 
                                                    | ((0x7fU 
                                                        == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                       | ((0x7fffU 
                                                           == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_25)) 
                                                          | ((0xffffU 
                                                              == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28)) 
                                                             | ((0x7fffU 
                                                                 == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_46)) 
                                                                | (0xffffU 
                                                                   == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48)))))))
                                                    ? 
                                                   ((1U 
                                                     & ((0xffU 
                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_9)) 
                                                        | ((IData)(
                                                                   (0x23U 
                                                                    == 
                                                                    (0x603fU 
                                                                     & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                           | ((0x7fffU 
                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_25)) 
                                                              | ((0xffffU 
                                                                  == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28)) 
                                                                 | ((0xffU 
                                                                     == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43)) 
                                                                    | ((0x7fffU 
                                                                        == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_46)) 
                                                                       | (0xffffU 
                                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48)))))))))
                                                     ? 
                                                    ((1U 
                                                      & ((0x7fU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                                         | ((0xffU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2)) 
                                                            | ((0xffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                                               | ((0x1ffU 
                                                                   == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_6)) 
                                                                  | ((IData)(
                                                                             (0x41U 
                                                                              == 
                                                                              (0xffefffc1U 
                                                                               & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                                     | ((0xffU 
                                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_15)) 
                                                                        | ((0x1ffU 
                                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_17)) 
                                                                           | ((0x7fU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                                              | ((0xffffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_36)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43)) 
                                                                                | (0xffffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48))))))))))))))
                                                      ? 
                                                     (0x1fU 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                         >> 0x14U))
                                                      : 
                                                     (0x3fU 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                         >> 0x14U)))
                                                     : 
                                                    ((1U 
                                                      & ((0x7fU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                                         | ((0xffU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2)) 
                                                            | ((0xffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                                               | ((0x1ffU 
                                                                   == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_6)) 
                                                                  | ((IData)(
                                                                             (0x41U 
                                                                              == 
                                                                              (0xffefffc1U 
                                                                               & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                                     | ((0xffU 
                                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_15)) 
                                                                        | ((0x1ffU 
                                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_17)) 
                                                                           | ((0x7fU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                                              | ((0xffffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_36)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43)) 
                                                                                | (0xffffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48))))))))))))))
                                                      ? 
                                                     (((- (IData)(
                                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                                   >> 0x1fU))) 
                                                       << 0x14U) 
                                                      | (((0xff000U 
                                                           & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst) 
                                                          | (0x800U 
                                                             & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                                >> 9U))) 
                                                         | (0x7feU 
                                                            & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                               >> 0x14U))))
                                                      : 
                                                     (0xfffff000U 
                                                      & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)))
                                                    : 
                                                   ((1U 
                                                     & ((0xffU 
                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_9)) 
                                                        | ((IData)(
                                                                   (0x23U 
                                                                    == 
                                                                    (0x603fU 
                                                                     & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                           | ((0x7fffU 
                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_25)) 
                                                              | ((0xffffU 
                                                                  == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28)) 
                                                                 | ((0xffU 
                                                                     == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43)) 
                                                                    | ((0x7fffU 
                                                                        == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_46)) 
                                                                       | (0xffffU 
                                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48)))))))))
                                                     ? 
                                                    ((1U 
                                                      & ((0x7fU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                                         | ((0xffU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2)) 
                                                            | ((0xffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                                               | ((0x1ffU 
                                                                   == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_6)) 
                                                                  | ((IData)(
                                                                             (0x41U 
                                                                              == 
                                                                              (0xffefffc1U 
                                                                               & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                                     | ((0xffU 
                                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_15)) 
                                                                        | ((0x1ffU 
                                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_17)) 
                                                                           | ((0x7fU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                                              | ((0xffffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_36)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43)) 
                                                                                | (0xffffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48))))))))))))))
                                                      ? 
                                                     (((- (IData)(
                                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                                   >> 0x1fU))) 
                                                       << 0xcU) 
                                                      | ((0x800U 
                                                          & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                             << 4U)) 
                                                         | ((0x7e0U 
                                                             & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                                >> 0x14U)) 
                                                            | (0x1eU 
                                                               & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                                  >> 7U)))))
                                                      : 
                                                     (((- (IData)(
                                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                                   >> 0x1fU))) 
                                                       << 0xcU) 
                                                      | ((0xfe0U 
                                                          & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                             >> 0x14U)) 
                                                         | (0x1fU 
                                                            & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                               >> 7U)))))
                                                     : 
                                                    ((1U 
                                                      & ((0x7fU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T)) 
                                                         | ((0xffU 
                                                             == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2)) 
                                                            | ((0xffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                                               | ((0x1ffU 
                                                                   == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_6)) 
                                                                  | ((IData)(
                                                                             (0x41U 
                                                                              == 
                                                                              (0xffefffc1U 
                                                                               & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                                     | ((0xffU 
                                                                         == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_15)) 
                                                                        | ((0x1ffU 
                                                                            == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_17)) 
                                                                           | ((0x7fU 
                                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                                              | ((0xffffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_36)) 
                                                                                | ((0xffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43)) 
                                                                                | (0xffffU 
                                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48))))))))))))))
                                                      ? 
                                                     (((- (IData)(
                                                                  (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                                   >> 0x1fU))) 
                                                       << 0xcU) 
                                                      | (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                         >> 0x14U))
                                                      : 0U)));
    vlSelfRef.CoreTop__DOT___idu_io_out_bruOp = (((
                                                   ((0x3ffU 
                                                     == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_18)) 
                                                    | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_65)) 
                                                   << 3U) 
                                                  | (4U 
                                                     & (((0x7fU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                         | (IData)(
                                                                   ((0x63U 
                                                                     == 
                                                                     (0x7fU 
                                                                      & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                    & ((IData)(
                                                                               (0x5000U 
                                                                                == 
                                                                                (0x5000U 
                                                                                & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                                       | (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_74))))) 
                                                        << 2U))) 
                                                 | ((2U 
                                                     & (((0x7fU 
                                                          == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                         | ((IData)(
                                                                    (0x1063U 
                                                                     == 
                                                                     (0x707fU 
                                                                      & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                            | ((IData)(
                                                                       ((0x63U 
                                                                         == 
                                                                         (0x7fU 
                                                                          & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                        & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_72))) 
                                                               | ((IData)(
                                                                          ((0x1063U 
                                                                            == 
                                                                            (0x107fU 
                                                                             & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                                           & (IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_74))) 
                                                                  | (0xfffffffU 
                                                                     == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_68))))) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & ((IData)(
                                                                  (0x63U 
                                                                   == 
                                                                   (0x307fU 
                                                                    & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                          | ((0x7fU 
                                                              == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19)) 
                                                             | ((0xfffffffU 
                                                                 == vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20) 
                                                                | (IData)(
                                                                          (0x4063U 
                                                                           == 
                                                                           (0x507fU 
                                                                            & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)))))))));
    vlSelfRef.CoreTop__DOT___idu_io_out_src1Sel = (
                                                   ((IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_65) 
                                                    << 2U) 
                                                   | ((((IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_66) 
                                                        | (0x37U 
                                                           == 
                                                           (0x7fU 
                                                            & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst))) 
                                                       << 1U) 
                                                      | ((IData)(vlSelfRef.CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_66) 
                                                         | (((0x17U 
                                                              == 
                                                              (0x7fU 
                                                               & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                             | (0x3ffU 
                                                                == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_18))) 
                                                            | (0x7fU 
                                                               == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19))))));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_3 = ((3U 
                                                 == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT__decodedBundle_wbTarget)) 
                                                & (IData)(
                                                          ((0U 
                                                            == 
                                                            (0xf8000U 
                                                             & vlSelfRef.CoreTop__DOT___ifu_io_sc_inst)) 
                                                           & ((2U 
                                                               == (IData)(vlSelfRef.CoreTop__DOT___wbu_io_csr_op)) 
                                                              | (3U 
                                                                 == (IData)(vlSelfRef.CoreTop__DOT___wbu_io_csr_op))))));
    vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0 = 
        ((0U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_src2Sel))
          ? vlSelfRef.CoreTop__DOT___regfile_io_rs2_data
          : ((1U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_src2Sel))
              ? vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp
              : ((2U == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_src2Sel))
                  ? 4U : 0U)));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_4 = ((9U 
                                                 == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp)) 
                                                | (0xaU 
                                                   == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp)));
    vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp = (
                                                   (4U 
                                                    & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_src1Sel))
                                                    ? 
                                                   ((2U 
                                                     & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_src1Sel))
                                                     ? 0U
                                                     : 
                                                    ((1U 
                                                      & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_src1Sel))
                                                      ? 0U
                                                      : vlSelfRef.CoreTop__DOT___csrfile_io_csr_rdata))
                                                    : 
                                                   ((2U 
                                                     & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_src1Sel))
                                                     ? 
                                                    ((1U 
                                                      & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_src1Sel))
                                                      ? 
                                                     (0x1fU 
                                                      & (vlSelfRef.CoreTop__DOT___ifu_io_sc_inst 
                                                         >> 0xfU))
                                                      : 0U)
                                                     : 
                                                    ((1U 
                                                      & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_src1Sel))
                                                      ? vlSelfRef.CoreTop__DOT__ifu__DOT__pcReg
                                                      : vlSelfRef.CoreTop__DOT___regfile_io_rs1_data)));
    vlSelfRef.io_commit_csr_wen = ((~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_3)) 
                                   & (3U == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT__decodedBundle_wbTarget)));
    vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data 
        = ((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_4)
            ? vlSelfRef.CoreTop__DOT___csrfile_io_csr_rdata
            : vlSelfRef.CoreTop__DOT___regfile_io_rs1_data);
    vlSelfRef.io_commit_csr_wdata = vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp;
    vlSelfRef.CoreTop__DOT__csrfile__DOT__new_val = 
        ((1U == (IData)(vlSelfRef.CoreTop__DOT___wbu_io_csr_op))
          ? vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp
          : ((2U == (IData)(vlSelfRef.CoreTop__DOT___wbu_io_csr_op))
              ? (vlSelfRef.CoreTop__DOT___csrfile_io_csr_rdata 
                 | vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp)
              : (((~ vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp) 
                  | (- (IData)((3U != (IData)(vlSelfRef.CoreTop__DOT___wbu_io_csr_op))))) 
                 & vlSelfRef.CoreTop__DOT___csrfile_io_csr_rdata)));
    vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT___GEN 
        = (((QData)((IData)((- (IData)((vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                                        >> 0x1fU))))) 
            << 0x20U) | (QData)((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp)));
    vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow 
        = ((0x80000000U == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp) 
           & (0xffffffffU == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0));
    vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp 
        = ((8U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
            ? ((4U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                ? 0U : ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                         ? ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                             ? 0U : vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp)
                         : ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                             ? (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                                < vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                             : VL_LTS_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))))
            : ((4U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                ? ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                    ? ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                        ? VL_SHIFTRS_III(32,32,32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, 
                                         (0x1fU & vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, 
                                        (0x1fU & vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))
                    : ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                        ? (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           << (0x1fU & vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                        : (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           ^ vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))
                : ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                    ? ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                        ? (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           | vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                        : (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           & vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                    : ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_aluOp))
                        ? (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           - vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                        : (vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp 
                           + vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))));
    vlSelfRef.io_commit_wen = ((0U != (IData)(vlSelfRef.io_commit_rd)) 
                               & ((1U == ((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_3)
                                           ? 1U : (IData)(vlSelfRef.CoreTop__DOT__idu__DOT__decodedBundle_wbTarget))) 
                                  | (IData)(vlSelfRef.io_commit_csr_wen)));
    vlSelfRef.CoreTop__DOT__exu__DOT__bru__DOT__casez_tmp 
        = ((8U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
            ? ((4U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                ? 0U : ((2U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                         ? ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                             ? 0U : vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data)
                         : ((1U & (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_bruOp))
                             ? vlSelfRef.CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data
                             : (0xfffffffeU & (vlSelfRef.CoreTop__DOT__idu__DOT__casez_tmp 
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
                        : 0U))));
    vlSelfRef.CoreTop__DOT___exu_io_out_aluOut = ((4U 
                                                   == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_fuType))
                                                   ? vlSelfRef.CoreTop__DOT___csrfile_io_csr_rdata
                                                   : 
                                                  ((3U 
                                                    == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_fuType))
                                                    ? 
                                                   ((8U 
                                                     == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                                     ? 
                                                    ((0U 
                                                      == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                                      ? vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp
                                                      : 
                                                     VL_MODDIV_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                                                     : 
                                                    ((7U 
                                                      == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                                      ? 
                                                     ((0U 
                                                       == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                                       ? vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp
                                                       : 
                                                      ((IData)(vlSelfRef.CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow)
                                                        ? 0U
                                                        : 
                                                       VL_MODDIVS_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)))
                                                      : 
                                                     ((6U 
                                                       == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                                       ? 
                                                      ((0U 
                                                        == vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0)
                                                        ? 0xffffffffU
                                                        : 
                                                       VL_DIV_III(32, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp, vlSelfRef.CoreTop__DOT__exu__DOT__casez_tmp_0))
                                                       : 
                                                      ((5U 
                                                        == (IData)(vlSelfRef.CoreTop__DOT___idu_io_out_mduOp))
                                                        ? 
                                                       ((0U 
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
                                                        : 
                                                       ((4U 
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
                                                            : 0U))))))))
                                                    : vlSelfRef.CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp));
    vlSelfRef.CoreTop__DOT__lsu__DOT___dpicLSU_io_rdata 
        = ((((1U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd)) 
             | (2U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd))) 
            & (2U != (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd)))
            ? (IData)(([&]() {
                    VCoreTop___024unit____Vdpiimwrap_pmem_read_TOP____024unit((QData)((IData)(
                                                                                (0xfffffffcU 
                                                                                & vlSelfRef.CoreTop__DOT___exu_io_out_aluOut))), 4U, vlSelfRef.__Vfunc_pmem_read__1__Vfuncout);
                }(), vlSelfRef.__Vfunc_pmem_read__1__Vfuncout))
            : 0U);
    vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
        = VL_SHIFTR_III(32,32,6, vlSelfRef.CoreTop__DOT__lsu__DOT___dpicLSU_io_rdata, 
                        (((3U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize)) 
                          | (2U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize)))
                          ? 0U : ((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                   ? (0x10U & (vlSelfRef.CoreTop__DOT___exu_io_out_aluOut 
                                               << 3U))
                                   : (0x18U & (vlSelfRef.CoreTop__DOT___exu_io_out_aluOut 
                                               << 3U)))));
    vlSelfRef.io_commit_wdata = ((1U == (IData)(vlSelfRef.CoreTop__DOT___lsu_io_out_memCmd))
                                  ? ((0U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                      ? (((- (IData)(
                                                     ((0xffU 
                                                       == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                                      & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                         >> 7U)))) 
                                          << 8U) | 
                                         (0xffU & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                      : ((1U == (IData)(vlSelfRef.CoreTop__DOT___exu_io_out_memSize))
                                          ? (((- (IData)(
                                                         ((0xffU 
                                                           == (IData)(vlSelfRef.CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4)) 
                                                          & (vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata 
                                                             >> 0xfU)))) 
                                              << 0x10U) 
                                             | (0xffffU 
                                                & vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                          : vlSelfRef.CoreTop__DOT__lsu__DOT__shiftedRdata))
                                  : vlSelfRef.CoreTop__DOT___exu_io_out_aluOut);
}
