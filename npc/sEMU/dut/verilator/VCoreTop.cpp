// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VCoreTop__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

VCoreTop::VCoreTop(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VCoreTop__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_commit_valid{vlSymsp->TOP.io_commit_valid}
    , io_commit_rd{vlSymsp->TOP.io_commit_rd}
    , io_commit_wen{vlSymsp->TOP.io_commit_wen}
    , io_commit_pc{vlSymsp->TOP.io_commit_pc}
    , io_commit_wdata{vlSymsp->TOP.io_commit_wdata}
    , __PVT____024unit{vlSymsp->TOP.__PVT____024unit}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

VCoreTop::VCoreTop(const char* _vcname__)
    : VCoreTop(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VCoreTop::~VCoreTop() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VCoreTop___024root___eval_debug_assertions(VCoreTop___024root* vlSelf);
#endif  // VL_DEBUG
void VCoreTop___024root___eval_static(VCoreTop___024root* vlSelf);
void VCoreTop___024root___eval_initial(VCoreTop___024root* vlSelf);
void VCoreTop___024root___eval_settle(VCoreTop___024root* vlSelf);
void VCoreTop___024root___eval(VCoreTop___024root* vlSelf);

void VCoreTop::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VCoreTop::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VCoreTop___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VCoreTop___024root___eval_static(&(vlSymsp->TOP));
        VCoreTop___024root___eval_initial(&(vlSymsp->TOP));
        VCoreTop___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VCoreTop___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VCoreTop::eventsPending() { return false; }

uint64_t VCoreTop::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VCoreTop::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VCoreTop___024root___eval_final(VCoreTop___024root* vlSelf);

VL_ATTR_COLD void VCoreTop::final() {
    VCoreTop___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VCoreTop::hierName() const { return vlSymsp->name(); }
const char* VCoreTop::modelName() const { return "VCoreTop"; }
unsigned VCoreTop::threads() const { return 1; }
void VCoreTop::prepareClone() const { contextp()->prepareClone(); }
void VCoreTop::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> VCoreTop::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void VCoreTop___024root__trace_decl_types(VerilatedVcd* tracep);

void VCoreTop___024root__trace_init_top(VCoreTop___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    VCoreTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VCoreTop___024root*>(voidSelf);
    VCoreTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    VCoreTop___024root__trace_decl_types(tracep);
    VCoreTop___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void VCoreTop___024root__trace_register(VCoreTop___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void VCoreTop::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'VCoreTop::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    VCoreTop___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
