#include "sEMU/difftest.hpp"
#include "sEMU/utils/colors.hpp"
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
        std::cerr << ANSI_COLOR_YELLOW << "[Difftest] No reference simulator provided. Difftest is disabled." << ANSI_COLOR_RESET << std::endl;
        return false;
    }

    std::cout << ANSI_COLOR_MAGENTA << "[Difftest] Loading reference simulator from " << ref_so_file << ANSI_COLOR_RESET << std::endl;

    handle = dlopen(ref_so_file.c_str(), RTLD_LAZY | RTLD_DEEPBIND);
    if (!handle) {
        std::cerr << ANSI_COLOR_RED << "[Difftest] Failed to load reference simulator: " << dlerror() << ANSI_COLOR_RESET << std::endl;
        return false;
    }

    auto load_symbol = [this](const char* name) -> void* {
        void* sym = dlsym(handle, name);
        if (!sym) {
            std::cerr << ANSI_COLOR_RED << "[Difftest] Failed to find symbol `" << name << "` in reference simulator." << ANSI_COLOR_RESET << std::endl;
            assert(0);
        }
        return sym;
    };

    ref_difftest_memcpy = reinterpret_cast<void(*)(uint32_t, void*, size_t, bool)>(load_symbol("difftest_memcpy"));
    ref_difftest_regcpy = reinterpret_cast<void(*)(void*, bool)>(load_symbol("difftest_regcpy"));
    ref_difftest_exec = reinterpret_cast<void(*)(uint64_t)>(load_symbol("difftest_exec"));
    ref_difftest_raise_intr = reinterpret_cast<void(*)(uint32_t)>(load_symbol("difftest_raise_intr"));
    ref_difftest_init = reinterpret_cast<void(*)(int)>(load_symbol("difftest_init"));

    // Load difftest_skip_ref symbol (optional, for MMIO handling)
    void* skip_sym = dlsym(handle, "difftest_skip_ref");
    if (skip_sym) {
        ref_difftest_skip_ref = reinterpret_cast<void(*)()>(skip_sym);
    } else {
        std::cerr << ANSI_COLOR_YELLOW << "[Difftest] Warning: difftest_skip_ref not found in reference simulator." << ANSI_COLOR_RESET << std::endl;
        ref_difftest_skip_ref = nullptr;
    }

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
        std::cerr << ANSI_COLOR_RED << "[Difftest] PC mismatch! DUT PC: " << std::hex << dut_state.pc
                  << " | REF PC: " << ref_r.pc << std::dec << ANSI_COLOR_RESET << std::endl;
        match = false;
    }

    for (int i = 0; i < 32; ++i) {
        uint32_t dut_val = dut_state.gpr[i];
        if (ref_r.gpr[i] != dut_val) {
            std::cerr << ANSI_COLOR_RED << "[Difftest] Register mismatch [" << i << "]! DUT: "
                      << std::hex << dut_val << " | REF: " << ref_r.gpr[i] << std::dec << ANSI_COLOR_RESET << std::endl;
            match = false;
        }
    }

    if (!match) {
        std::cerr << ANSI_COLOR_RED << "[Difftest] DUT Registers:\n";
        for (int i = 0; i < 32; ++i) {
             std::cerr << "  x" << std::dec << i << ": 0x" << std::hex << dut_state.gpr[i] << "\n";
        }
        std::cerr << "  pc: 0x" << std::hex << dut_state.pc << "\n";

        std::cerr << "[Difftest] REF Registers:\n";
        CPU_state ref_r2;
        ref_difftest_regcpy(&ref_r2, DIFFTEST_TO_DUT);
        for (int i = 0; i < 32; ++i) {
             std::cerr << "  x" << std::dec << i << ": 0x" << std::hex << ref_r2.gpr[i] << "\n";
        }
        std::cerr << "  pc: 0x" << std::hex << ref_r2.pc << "\n";

        std::cerr << "[Difftest] Stopping execution due to mismatch." << ANSI_COLOR_RESET << std::endl;
        return false;
    }

    return true;
}

void DiffTest::skip_ref() {
    if (!active) return;
    if (ref_difftest_skip_ref) {
        ref_difftest_skip_ref();
    }
}
