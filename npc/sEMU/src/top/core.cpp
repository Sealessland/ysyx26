#include "sEMU/core.hpp"
#include "sEMU/mem.hpp"
#include "VCoreTop.h"
#include "VCoreTop___024root.h"
#include "VCoreTop__Dpi.h"
#include "verilated.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

guest_mem* p_mem = nullptr;
Core* p_core = nullptr;

bool g_trace_mem = false;
std::vector<std::string> mem_access_log;

// 用 volatile 计数器产生可见副作用，防止编译器把 npc_ebreak 整体优化消除
static volatile int g_ebreak_count = 0;

extern "C" {
    void npc_ebreak() {
        // 写入 volatile 变量：编译器无法证明此写无副作用，必须保留
        g_ebreak_count++;
        // 全编译器内存屏障：禁止跨此点做任何内存访问重排或 dead-store 消除
        asm volatile("" ::: "memory");

        std::cout << "EBREAK executing, stopping simulation! (count=" 
                  << g_ebreak_count << ")" << std::endl;
        if (p_core) {
            p_core->state = CoreState::END;
            // 再做一次写后屏障，确保 state 赋值对其他线程/eval 上下文可见
            asm volatile("" ::: "memory");
        }
    }

    bool in_bounds(size_t addr) {
        if (!p_mem) return false;
        return p_mem->in_bounds(addr);
    }

    int paddr_read(int io_raddr) {
        //trans into hex
        size_t addr = static_cast<size_t>(io_raddr) & 0xFFFFFFFF;
        if (in_bounds(addr)) {
            return p_mem->lw(addr);
        }
        return 0; // 或者返回指定错误指令
    }

    long long pmem_read(long long raddr, char io_len) {
        size_t addr = static_cast<size_t>(raddr);
        long long val = 0;
        if (in_bounds(addr)) {
            switch (io_len) {
                case 1: val = p_mem->lbu(addr); break;
                case 2: val = p_mem->lhu(addr); break;
                case 4: val = p_mem->lwu(addr); break;
                case 8: val = p_mem->ld(addr); break;
            }
        }
        if (g_trace_mem) {
            std::stringstream ss;
            ss << "Read  [0x" << std::hex << addr << "] len=" << std::dec << (int)io_len 
               << " val=0x" << std::hex << val;
            mem_access_log.push_back(ss.str());
        }
        return val;
    }

    void pmem_write(long long waddr, long long io_wdata, char io_len) {
        size_t addr = static_cast<size_t>(waddr);
        if (in_bounds(addr)) {
            switch (io_len) {
                case 1: p_mem->sb(addr, static_cast<uint8_t>(io_wdata)); break;
                case 2: p_mem->sh(addr, static_cast<uint16_t>(io_wdata)); break;
                case 4: p_mem->sw(addr, static_cast<uint32_t>(io_wdata)); break;
                case 8: p_mem->sd(addr, static_cast<uint64_t>(io_wdata)); break;
            }
        }
        if (g_trace_mem) {
            std::stringstream ss;
            ss << "Write [0x" << std::hex << addr << "] len=" << std::dec << (int)io_len 
               << " val=0x" << std::hex << io_wdata;
            mem_access_log.push_back(ss.str());
        }
    }
}

Core::Core(guest_mem* mem_instance) 
    : contextp(std::make_unique<VerilatedContext>()),
      top(std::make_unique<VCoreTop>(contextp.get())),
      state(CoreState::STOPPED)
{
    p_mem = mem_instance;
    p_core = this;
    // 初始化引脚状态
    top->clock = 0;
    top->reset = 0;
    eval();
}

Core::~Core() {
    top->final();
}

void Core::eval() {
    top->eval();
    contextp->timeInc(1);
}

void Core::step() {
    top->clock = 0;
    eval();
    top->clock = 1;
    eval();
}

void Core::reset(int cycles) {
    top->reset = 1;
    for (int i = 0; i < cycles; ++i) {
        step();
    }
    top->reset = 0;
}

bool Core::is_commit_valid() const {
    return top->io_commit_valid;
}

uint32_t Core::get_commit_pc() const {
    return top->io_commit_pc;
}

uint32_t Core::get_commit_wdata() const {
    return top->io_commit_wdata;
}

uint8_t Core::get_commit_rd() const {
    return top->io_commit_rd;
}

bool Core::is_commit_wen() const {
    return top->io_commit_wen;
}

const char* reg_names[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void Core::print_registers() const {
    for (int i = 0; i < 32; ++i) {
        std::cout << std::setw(4) << std::setfill(' ') << reg_names[i] << ": 0x" 
                << std::hex << std::setw(8) << std::setfill('0') 
                << top->rootp->CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[i]
                << (i % 4 == 3 ? "\n" : "    ");
    }
    std::cout << std::setw(4) << std::setfill(' ') << "pc" << ": 0x" 
                << std::hex << std::setw(8) << std::setfill('0')
                << top->rootp->CoreTop__DOT__ifu__DOT__pcReg << "\n" << std::dec;
}

uint32_t Core::get_reg_by_name(const std::string& name) const {
    if (name == "pc") {
        return top->rootp->CoreTop__DOT__ifu__DOT__pcReg;
    }
    for (int i = 0; i < 32; ++i) {
        if (name == reg_names[i] || name == "x" + std::to_string(i)) {
            return top->rootp->CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[i];
        }
    }
    std::cerr << "Unknown register: " << name << std::endl;
    return 0;
}

uint32_t Core::get_reg(int idx) const {
    if (idx < 0 || idx >= 32) return 0;
    return top->rootp->CoreTop__DOT__regfile__DOT__regs_ext__DOT__Memory[idx];
}