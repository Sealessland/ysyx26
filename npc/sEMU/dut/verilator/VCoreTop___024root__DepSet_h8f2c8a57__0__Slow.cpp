// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCoreTop.h for the primary calling header

#include "VCoreTop__pch.h"
#include "VCoreTop___024root.h"

VL_ATTR_COLD void VCoreTop___024root___eval_static(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___eval_static\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
}

VL_ATTR_COLD void VCoreTop___024root___eval_initial__TOP(VCoreTop___024root* vlSelf);

VL_ATTR_COLD void VCoreTop___024root___eval_initial(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___eval_initial\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VCoreTop___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void VCoreTop___024root___eval_initial__TOP(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___eval_initial__TOP\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.io_commit_valid = 1U;
}

VL_ATTR_COLD void VCoreTop___024root___eval_final(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___eval_final\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCoreTop___024root___dump_triggers__stl(VCoreTop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VCoreTop___024root___eval_phase__stl(VCoreTop___024root* vlSelf);

VL_ATTR_COLD void VCoreTop___024root___eval_settle(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___eval_settle\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            VCoreTop___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("../../build/CoreTop.sv", 2, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (VCoreTop___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCoreTop___024root___dump_triggers__stl(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___dump_triggers__stl\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VCoreTop___024root___stl_sequent__TOP__0(VCoreTop___024root* vlSelf);
VL_ATTR_COLD void VCoreTop___024root____Vm_traceActivitySetAll(VCoreTop___024root* vlSelf);

VL_ATTR_COLD void VCoreTop___024root___eval_stl(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___eval_stl\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VCoreTop___024root___stl_sequent__TOP__0(vlSelf);
        VCoreTop___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void VCoreTop___024root___eval_triggers__stl(VCoreTop___024root* vlSelf);

VL_ATTR_COLD bool VCoreTop___024root___eval_phase__stl(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___eval_phase__stl\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    VCoreTop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        VCoreTop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCoreTop___024root___dump_triggers__act(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___dump_triggers__act\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VCoreTop___024root___dump_triggers__nba(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___dump_triggers__nba\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VCoreTop___024root____Vm_traceActivitySetAll(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root____Vm_traceActivitySetAll\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void VCoreTop___024root___ctor_var_reset(VCoreTop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCoreTop___024root___ctor_var_reset\n"); );
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_commit_pc = VL_RAND_RESET_I(32);
    vlSelf->io_commit_inst = VL_RAND_RESET_I(32);
    vlSelf->io_commit_valid = VL_RAND_RESET_I(1);
    vlSelf->io_commit_is_store = VL_RAND_RESET_I(1);
    vlSelf->io_commit_halt = VL_RAND_RESET_I(1);
    vlSelf->io_commit_rd = VL_RAND_RESET_I(5);
    vlSelf->io_commit_wdata = VL_RAND_RESET_I(32);
    vlSelf->io_commit_wen = VL_RAND_RESET_I(1);
    vlSelf->io_commit_csr_waddr = VL_RAND_RESET_I(12);
    vlSelf->io_commit_csr_wdata = VL_RAND_RESET_I(32);
    vlSelf->io_commit_csr_wen = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT___csrfile_io_csr_rdata = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT___regfile_io_rs1_data = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT___regfile_io_rs2_data = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT___wbu_io_csr_op = VL_RAND_RESET_I(3);
    vlSelf->CoreTop__DOT___lsu_io_out_memCmd = VL_RAND_RESET_I(2);
    vlSelf->CoreTop__DOT___exu_io_out_aluOut = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT___exu_io_out_memSize = VL_RAND_RESET_I(2);
    vlSelf->CoreTop__DOT___idu_io_out_fuType = VL_RAND_RESET_I(3);
    vlSelf->CoreTop__DOT___idu_io_out_src1Sel = VL_RAND_RESET_I(3);
    vlSelf->CoreTop__DOT___idu_io_out_src2Sel = VL_RAND_RESET_I(2);
    vlSelf->CoreTop__DOT___idu_io_out_aluOp = VL_RAND_RESET_I(4);
    vlSelf->CoreTop__DOT___idu_io_out_bruOp = VL_RAND_RESET_I(4);
    vlSelf->CoreTop__DOT___idu_io_out_mduOp = VL_RAND_RESET_I(4);
    vlSelf->CoreTop__DOT___ifu_io_sc_inst = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__ifu__DOT__pcReg = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T = VL_RAND_RESET_I(7);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1 = VL_RAND_RESET_I(8);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2 = VL_RAND_RESET_I(8);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3 = VL_RAND_RESET_I(7);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4 = VL_RAND_RESET_I(8);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_5 = VL_RAND_RESET_I(10);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_6 = VL_RAND_RESET_I(9);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_7 = VL_RAND_RESET_I(6);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_9 = VL_RAND_RESET_I(8);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_15 = VL_RAND_RESET_I(8);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_17 = VL_RAND_RESET_I(9);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_18 = VL_RAND_RESET_I(10);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19 = VL_RAND_RESET_I(7);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20 = VL_RAND_RESET_I(28);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21 = VL_RAND_RESET_I(28);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_25 = VL_RAND_RESET_I(15);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_27 = VL_RAND_RESET_I(15);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28 = VL_RAND_RESET_I(16);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_33 = VL_RAND_RESET_I(8);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_36 = VL_RAND_RESET_I(8);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_39 = VL_RAND_RESET_I(8);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43 = VL_RAND_RESET_I(8);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_46 = VL_RAND_RESET_I(15);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_47 = VL_RAND_RESET_I(15);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48 = VL_RAND_RESET_I(16);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_49 = VL_RAND_RESET_I(15);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_67 = VL_RAND_RESET_I(28);
    vlSelf->CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_68 = VL_RAND_RESET_I(28);
    vlSelf->CoreTop__DOT__idu__DOT__decodedBundle_wbTarget = VL_RAND_RESET_I(2);
    vlSelf->CoreTop__DOT__idu__DOT__casez_tmp = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_44 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_53 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_61 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_65 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_66 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_68 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_69 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_70 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_71 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_72 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_73 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_74 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_75 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_76 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_77 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_78 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_79 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_80 = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_81 = VL_RAND_RESET_I(3);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_82 = VL_RAND_RESET_I(2);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_83 = VL_RAND_RESET_I(3);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_84 = VL_RAND_RESET_I(5);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_85 = VL_RAND_RESET_I(7);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_86 = VL_RAND_RESET_I(2);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_87 = VL_RAND_RESET_I(3);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_88 = VL_RAND_RESET_I(6);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_89 = VL_RAND_RESET_I(7);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_90 = VL_RAND_RESET_I(11);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_91 = VL_RAND_RESET_I(10);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_92 = VL_RAND_RESET_I(5);
    vlSelf->CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_93 = VL_RAND_RESET_I(10);
    vlSelf->CoreTop__DOT__exu__DOT__casez_tmp = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__exu__DOT__casez_tmp_0 = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow = VL_RAND_RESET_I(1);
    vlSelf->CoreTop__DOT__exu__DOT__mdu__DOT___GEN = VL_RAND_RESET_Q(64);
    vlSelf->CoreTop__DOT__exu__DOT__bru__DOT__casez_tmp = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__lsu__DOT___dpicLSU_io_rdata = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__lsu__DOT__shiftedRdata = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->CoreTop__DOT__csrfile__DOT__mstatus = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__csrfile__DOT__mtvec = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__csrfile__DOT__mepc = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__csrfile__DOT__mcause = VL_RAND_RESET_I(32);
    vlSelf->CoreTop__DOT__csrfile__DOT__new_val = VL_RAND_RESET_I(32);
    vlSelf->__VdfgRegularize_hd87f99a1_1_3 = VL_RAND_RESET_I(1);
    vlSelf->__VdfgRegularize_hd87f99a1_1_4 = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_paddr_read__0__Vfuncout = 0;
    vlSelf->__Vfunc_pmem_read__1__Vfuncout = 0;
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
