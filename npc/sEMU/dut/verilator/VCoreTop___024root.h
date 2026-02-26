// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VCoreTop.h for the primary calling header

#ifndef VERILATED_VCORETOP___024ROOT_H_
#define VERILATED_VCORETOP___024ROOT_H_  // guard

#include "verilated.h"
class VCoreTop___024unit;


class VCoreTop__Syms;

class alignas(VL_CACHE_LINE_BYTES) VCoreTop___024root final : public VerilatedModule {
  public:
    // CELLS
    VCoreTop___024unit* __PVT____024unit;

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clock,0,0);
        VL_IN8(reset,0,0);
        VL_OUT8(io_commit_valid,0,0);
        VL_OUT8(io_commit_is_store,0,0);
        VL_OUT8(io_commit_halt,0,0);
        VL_OUT8(io_commit_rd,4,0);
        VL_OUT8(io_commit_wen,0,0);
        VL_OUT8(io_commit_csr_wen,0,0);
        CData/*2:0*/ CoreTop__DOT___wbu_io_csr_op;
        CData/*1:0*/ CoreTop__DOT___lsu_io_out_memCmd;
        CData/*1:0*/ CoreTop__DOT___exu_io_out_memSize;
        CData/*2:0*/ CoreTop__DOT___idu_io_out_fuType;
        CData/*2:0*/ CoreTop__DOT___idu_io_out_src1Sel;
        CData/*1:0*/ CoreTop__DOT___idu_io_out_src2Sel;
        CData/*3:0*/ CoreTop__DOT___idu_io_out_aluOp;
        CData/*3:0*/ CoreTop__DOT___idu_io_out_bruOp;
        CData/*3:0*/ CoreTop__DOT___idu_io_out_mduOp;
        CData/*6:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2;
        CData/*6:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4;
        CData/*5:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_7;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_9;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_15;
        CData/*6:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_33;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_36;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_39;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_43;
        CData/*1:0*/ CoreTop__DOT__idu__DOT__decodedBundle_wbTarget;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_44;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_53;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_61;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_65;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_66;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_68;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_69;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_70;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_71;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_72;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_73;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_74;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_75;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_76;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_77;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_78;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_79;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_80;
        CData/*2:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_81;
        CData/*1:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_82;
        CData/*2:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_83;
        CData/*4:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_84;
        CData/*6:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_85;
        CData/*1:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_86;
        CData/*2:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_87;
        CData/*5:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_88;
        CData/*6:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_89;
        CData/*4:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_92;
        CData/*0:0*/ CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow;
        CData/*0:0*/ __VdfgRegularize_hd87f99a1_1_3;
        CData/*0:0*/ __VdfgRegularize_hd87f99a1_1_4;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
    };
    struct {
        CData/*0:0*/ __VactContinue;
        VL_OUT16(io_commit_csr_waddr,11,0);
        SData/*9:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_5;
        SData/*8:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_6;
        SData/*8:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_17;
        SData/*9:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_18;
        SData/*14:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_25;
        SData/*14:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_27;
        SData/*15:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_28;
        SData/*14:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_46;
        SData/*14:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_47;
        SData/*15:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_48;
        SData/*14:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_49;
        SData/*10:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_90;
        SData/*9:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_91;
        SData/*9:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_93;
        VL_OUT(io_commit_pc,31,0);
        VL_OUT(io_commit_inst,31,0);
        VL_OUT(io_commit_wdata,31,0);
        VL_OUT(io_commit_csr_wdata,31,0);
        IData/*31:0*/ CoreTop__DOT___csrfile_io_csr_rdata;
        IData/*31:0*/ CoreTop__DOT___regfile_io_rs1_data;
        IData/*31:0*/ CoreTop__DOT___regfile_io_rs2_data;
        IData/*31:0*/ CoreTop__DOT___exu_io_out_aluOut;
        IData/*31:0*/ CoreTop__DOT___ifu_io_sc_inst;
        IData/*31:0*/ CoreTop__DOT__ifu__DOT__pcReg;
        IData/*27:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20;
        IData/*27:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21;
        IData/*27:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_67;
        IData/*27:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_68;
        IData/*31:0*/ CoreTop__DOT__idu__DOT__casez_tmp;
        IData/*31:0*/ CoreTop__DOT__exu__DOT__casez_tmp;
        IData/*31:0*/ CoreTop__DOT__exu__DOT__casez_tmp_0;
        IData/*31:0*/ CoreTop__DOT__exu__DOT____Vcellinp__bru__io_rs1_data;
        IData/*31:0*/ CoreTop__DOT__exu__DOT__alu__DOT__casez_tmp;
        IData/*31:0*/ CoreTop__DOT__exu__DOT__bru__DOT__casez_tmp;
        IData/*31:0*/ CoreTop__DOT__lsu__DOT___dpicLSU_io_rdata;
        IData/*31:0*/ CoreTop__DOT__lsu__DOT__shiftedRdata;
        IData/*31:0*/ CoreTop__DOT__csrfile__DOT__mstatus;
        IData/*31:0*/ CoreTop__DOT__csrfile__DOT__mtvec;
        IData/*31:0*/ CoreTop__DOT__csrfile__DOT__mepc;
        IData/*31:0*/ CoreTop__DOT__csrfile__DOT__mcause;
        IData/*31:0*/ CoreTop__DOT__csrfile__DOT__new_val;
        IData/*31:0*/ __Vfunc_paddr_read__0__Vfuncout;
        IData/*31:0*/ __VactIterCount;
        QData/*63:0*/ CoreTop__DOT__exu__DOT__mdu__DOT___GEN;
        QData/*63:0*/ __Vfunc_pmem_read__1__Vfuncout;
        VlUnpacked<IData/*31:0*/, 32> CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory;
        VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    VCoreTop__Syms* const vlSymsp;

    // CONSTRUCTORS
    VCoreTop___024root(VCoreTop__Syms* symsp, const char* v__name);
    ~VCoreTop___024root();
    VL_UNCOPYABLE(VCoreTop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
