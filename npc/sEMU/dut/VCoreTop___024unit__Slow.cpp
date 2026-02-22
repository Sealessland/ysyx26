// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCoreTop.h for the primary calling header

#include "VCoreTop__pch.h"
#include "VCoreTop__Syms.h"
#include "VCoreTop___024unit.h"

void VCoreTop___024unit___ctor_var_reset(VCoreTop___024unit* vlSelf);

VCoreTop___024unit::VCoreTop___024unit(VCoreTop__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    VCoreTop___024unit___ctor_var_reset(this);
}

void VCoreTop___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VCoreTop___024unit::~VCoreTop___024unit() {
}
