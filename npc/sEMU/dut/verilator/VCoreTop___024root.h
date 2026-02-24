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
        VL_OUT8(io_commit_rd,4,0);
        VL_OUT8(io_commit_wen,0,0);
        CData/*2:0*/ CoreTop__DOT___wbu_io_csr_op;
        CData/*1:0*/ CoreTop__DOT___lsu_io_out_wbTarget;
        CData/*1:0*/ CoreTop__DOT___exu_io_out_memCmd;
        CData/*1:0*/ CoreTop__DOT___exu_io_out_memSize;
        CData/*0:0*/ CoreTop__DOT___exu_io_out_memSign;
        CData/*2:0*/ CoreTop__DOT___idu_io_out_src1Sel;
        CData/*1:0*/ CoreTop__DOT___idu_io_out_src2Sel;
        CData/*3:0*/ CoreTop__DOT___idu_io_out_aluOp;
        CData/*3:0*/ CoreTop__DOT___idu_io_out_bruOp;
        CData/*3:0*/ CoreTop__DOT___idu_io_out_mduOp;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_1;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_2;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_3;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_5;
        CData/*5:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_8;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_17;
        CData/*6:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_21;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_29;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_31;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_34;
        CData/*7:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_38;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_47;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_54;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_55;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_60;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_61;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_62;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_63;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_64;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_65;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_67;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_68;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_69;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_70;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_71;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_72;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_73;
        CData/*0:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_74;
        CData/*2:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_76;
        CData/*3:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_77;
        CData/*1:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_78;
        CData/*2:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_79;
        CData/*6:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_80;
        CData/*1:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_81;
        CData/*2:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_82;
        CData/*5:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_83;
        CData/*0:0*/ CoreTop__DOT__exu__DOT__mdu__DOT__isOverflow;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
        CData/*0:0*/ __VactContinue;
        SData/*11:0*/ CoreTop__DOT___wbu_io_csr_waddr;
        SData/*8:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_4;
        SData/*9:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_7;
        SData/*8:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_10;
        SData/*8:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_19;
        SData/*9:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_20;
        SData/*15:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_41;
        SData/*13:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_51;
    };
    struct {
        SData/*10:0*/ CoreTop__DOT__idu__DOT____VdfgRegularize_hdcfcc17d_0_84;
        VL_OUT(io_commit_pc,31,0);
        VL_OUT(io_commit_wdata,31,0);
        IData/*31:0*/ CoreTop__DOT___csrfile_io_csr_rdata;
        IData/*31:0*/ CoreTop__DOT___regfile_io_rs1_data;
        IData/*31:0*/ CoreTop__DOT___regfile_io_rs2_data;
        IData/*31:0*/ CoreTop__DOT___exu_io_out_aluOut;
        IData/*31:0*/ CoreTop__DOT___ifu_io_sc_inst;
        IData/*31:0*/ CoreTop__DOT__ifu__DOT__pcReg;
        IData/*27:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_22;
        IData/*27:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_23;
        IData/*27:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_59;
        IData/*27:0*/ CoreTop__DOT__idu__DOT___decodedBundle_andMatrixOutputs_T_60;
        IData/*31:0*/ CoreTop__DOT__idu__DOT__casez_tmp;
        IData/*31:0*/ CoreTop__DOT__exu__DOT__casez_tmp;
        IData/*31:0*/ CoreTop__DOT__exu__DOT__casez_tmp_0;
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
