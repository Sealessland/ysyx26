#include "sEMU/difftest.hpp"
#include <iostream>
#include <dlfcn.h>
#include <cassert>

// Define the global difftest instance.
DiffTest difftest;

DiffTest::DiffTest() {}

DiffTest::~DiffTest() {
    if (handle) {
        dlclose(handle);
    }
}

bool DiffTest::init(const std::string& ref_so_file, int port) {
    if (ref_so_file.empty()) {
        std::cerr << "[Difftest] No reference simulator provided. Difftest is disabled." << std::endl;
        return false;
    }

    std::cout << "[Difftest] Loading reference simulator from " << ref_so_file << std::endl;

    handle = dlopen(ref_so_file.c_str(), RTLD_LAZY | RTLD_DEEPBIND);
    if (!handle) {
        std::cerr << "[Difftest] Failed to load reference simulator: " << dlerror() << std::endl;
        return false;
    }

    auto load_symbol = [this](const char* name) -> void* {
        void* sym = dlsym(handle, name);
        if (!sym) {
            std::cerr << "[Difftest] Failed to find symbol `" << name << "` in reference simulator." << std::endl;
            assert(0);
        }
        return sym;
    };

    ref_difftest_memcpy = reinterpret_cast<void(*)(uint32_t, void*, size_t, bool)>(load_symbol("difftest_memcpy"));
    ref_difftest_regcpy = reinterpret_cast<void(*)(void*, bool)>(load_symbol("difftest_regcpy"));
    ref_difftest_exec = reinterpret_cast<void(*)(uint64_t)>(load_symbol("difftest_exec"));
    ref_difftest_raise_intr = reinterpret_cast<void(*)(uint32_t)>(load_symbol("difftest_raise_intr"));
    ref_difftest_init = reinterpret_cast<void(*)(int)>(load_symbol("difftest_init"));

    // Initialize ref simulator
    ref_difftest_init(port);
    
    active = true;
    return true;
}

void DiffTest::sync_memory(size_t addr, void* buf, size_t n, bool to_ref) {
    if (!active) return;
    ref_difftest_memcpy(addr, buf, n, to_ref ? DIFFTEST_TO_REF : DIFFTEST_TO_DUT);
}

void DiffTest::sync_registers(const Core* core, bool to_ref) {
    if (!active) return;
    CPU_state state;
    if (to_ref) {
        for (int i = 0; i < 32; ++i) {
            state.gpr[i] = core->get_reg(i);
        }
        state.pc = core->get_reg_by_name("pc");
        ref_difftest_regcpy(&state, DIFFTEST_TO_REF);
    } else {
        ref_difftest_regcpy(&state, DIFFTEST_TO_DUT);
        for (int i = 0; i < 32; ++i) {
            // Usually we don't sync registers *back* to DUT in simple difftest framework.
            // If needed, you would set core registers here.
            // core->set_reg(i, state.gpr[i]);
        }
        // core->set_pc(state.pc);
    }
}

void DiffTest::step(uint64_t n) {
    if (!active) return;
    ref_difftest_exec(n);
}

bool DiffTest::check_registers(const CPU_state& dut_state) {
    if (!active) return true;

    CPU_state ref_r;
    ref_difftest_regcpy(&ref_r, DIFFTEST_TO_DUT);

    bool match = true;
    if (ref_r.pc != dut_state.pc) {
        std::cerr << "[Difftest] PC mismatch! DUT PC: " << std::hex << dut_state.pc
                  << " | REF PC: " << ref_r.pc << std::dec << std::endl;
        match = false;
    }

    for (int i = 0; i < 32; ++i) {
        uint32_t dut_val = dut_state.gpr[i];
        if (ref_r.gpr[i] != dut_val) {
            std::cerr << "[Difftest] Register mismatch [" << i << "]! DUT: " 
                      << std::hex << dut_val << " | REF: " << ref_r.gpr[i] << std::dec << std::endl;
            match = false;
        }
    }

    if (!match) {
        std::cerr << "[Difftest] DUT Registers:\n";
        for (int i = 0; i < 32; ++i) {
             std::cerr << "  x" << i << ": 0x" << std::hex << dut_state.gpr[i] << std::dec << "\n";
        }
        std::cerr << "  pc: 0x" << std::hex << dut_state.pc << std::dec << "\n";
        return false;
    }

    return true;
}
