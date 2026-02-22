// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VCORETOP__DPI_H_
#define VERILATED_VCORETOP__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at DPIC_Ebreak.sv:2:30
    extern void npc_ebreak();
    // DPI import at DPIC_Fetch.sv:2:29
    extern int paddr_read(int io_raddr);
    // DPI import at DPIC_LSU.sv:2:33
    extern long long pmem_read(long long raddr, char io_len);
    // DPI import at DPIC_LSU.sv:3:30
    extern void pmem_write(long long waddr, long long io_wdata, char io_len);

#ifdef __cplusplus
}
#endif

#endif  // guard
