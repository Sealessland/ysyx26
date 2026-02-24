// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCoreTop.h for the primary calling header

#include "VCoreTop__pch.h"
#include "VCoreTop__Syms.h"
#include "VCoreTop___024unit.h"

extern "C" int paddr_read(int io_raddr);

VL_INLINE_OPT void VCoreTop___024unit____Vdpiimwrap_paddr_read_TOP____024unit(IData/*31:0*/ io_raddr, IData/*31:0*/ &paddr_read__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VCoreTop___024unit____Vdpiimwrap_paddr_read_TOP____024unit\n"); );
    // Body
    int io_raddr__Vcvt;
    for (size_t io_raddr__Vidx = 0; io_raddr__Vidx < 1; ++io_raddr__Vidx) io_raddr__Vcvt = io_raddr;
    int paddr_read__Vfuncrtn__Vcvt;
    paddr_read__Vfuncrtn__Vcvt = paddr_read(io_raddr__Vcvt);
    paddr_read__Vfuncrtn = paddr_read__Vfuncrtn__Vcvt;
}

extern "C" long long pmem_read(long long raddr, char io_len);

VL_INLINE_OPT void VCoreTop___024unit____Vdpiimwrap_pmem_read_TOP____024unit(QData/*63:0*/ raddr, CData/*7:0*/ io_len, QData/*63:0*/ &pmem_read__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VCoreTop___024unit____Vdpiimwrap_pmem_read_TOP____024unit\n"); );
    // Body
    long long raddr__Vcvt;
    for (size_t raddr__Vidx = 0; raddr__Vidx < 1; ++raddr__Vidx) raddr__Vcvt = raddr;
    char io_len__Vcvt;
    for (size_t io_len__Vidx = 0; io_len__Vidx < 1; ++io_len__Vidx) io_len__Vcvt = io_len;
    long long pmem_read__Vfuncrtn__Vcvt;
    pmem_read__Vfuncrtn__Vcvt = pmem_read(raddr__Vcvt, io_len__Vcvt);
    pmem_read__Vfuncrtn = pmem_read__Vfuncrtn__Vcvt;
}

extern "C" void pmem_write(long long waddr, long long io_wdata, char io_len);

VL_INLINE_OPT void VCoreTop___024unit____Vdpiimwrap_pmem_write_TOP____024unit(QData/*63:0*/ waddr, QData/*63:0*/ io_wdata, CData/*7:0*/ io_len) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VCoreTop___024unit____Vdpiimwrap_pmem_write_TOP____024unit\n"); );
    // Body
    long long waddr__Vcvt;
    for (size_t waddr__Vidx = 0; waddr__Vidx < 1; ++waddr__Vidx) waddr__Vcvt = waddr;
    long long io_wdata__Vcvt;
    for (size_t io_wdata__Vidx = 0; io_wdata__Vidx < 1; ++io_wdata__Vidx) io_wdata__Vcvt = io_wdata;
    char io_len__Vcvt;
    for (size_t io_len__Vidx = 0; io_len__Vidx < 1; ++io_len__Vidx) io_len__Vcvt = io_len;
    pmem_write(waddr__Vcvt, io_wdata__Vcvt, io_len__Vcvt);
}

extern "C" void npc_ebreak();

VL_INLINE_OPT void VCoreTop___024unit____Vdpiimwrap_npc_ebreak_TOP____024unit() {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VCoreTop___024unit____Vdpiimwrap_npc_ebreak_TOP____024unit\n"); );
    // Body
    npc_ebreak();
}
