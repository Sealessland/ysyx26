#include "sEMU/core.hpp"
#include "sEMU/mem.hpp"
#include "VCoreTop.h"
#include "VCoreTop___024root.h"
#include "VCoreTop__Dpi.h"
#include "verilated.h"
#include "verilated_vcd_c.h"  // VCD trace 支持
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

Core::Core(guest_mem* mem_instance, const std::string& vcd_path)
    : contextp(std::make_unique<VerilatedContext>()),
      top(std::make_unique<VCoreTop>(contextp.get())),
      state(CoreState::STOPPED)
{
    p_mem = mem_instance;
    p_core = this;

    // 若要录波形，traceEverOn 必须在首次 eval 前调用
    if (!vcd_path.empty()) {
        contextp->traceEverOn(true);
    }

    // 初始化引脚状态
    top->clock = 0;
    top->reset = 0;
    eval();

    // 首次 eval 后再 attach trace，确保内部数据结构已初始化
    if (!vcd_path.empty()) {
        tfp_ = new VerilatedVcdC;
        top->trace(tfp_, 0);
        tfp_->open(vcd_path.c_str());
        if (!tfp_->isOpen()) {
            std::cerr << "[Trace] 无法打开 VCD 文件: " << vcd_path << std::endl;
            delete tfp_;
            tfp_ = nullptr;
        } else {
            // 文件就绪，但默认处于暂停——需要 trace_start() 才开始写入
            std::cout << "[Trace] 波形就绪（暂停）：" << vcd_path
                      << "  输入 'wave start' 开始录制" << std::endl;
            // trace_enabled_ 保持 false
        }
    }
}

Core::~Core() {
    close_trace(); // 确保析构时刷新并关闭波形文件
    top->final();
}

void Core::open_trace(const std::string& vcd_path, int depth) {
    if (tfp_) {
        std::cerr << "[Trace] 波形文件已经打开，请先 close_trace()" << std::endl;
        return;
    }
    // 如果 traceEverOn 未在构造时设置，这里作为兼容尝试
    contextp->traceEverOn(true);
    tfp_ = new VerilatedVcdC;
    top->trace(tfp_, depth);
    tfp_->open(vcd_path.c_str());
    if (!tfp_->isOpen()) {
        std::cerr << "[Trace] 无法打开 VCD 文件: " << vcd_path << std::endl;
        delete tfp_;
        tfp_ = nullptr;
    } else {
        // 文件已就绪，等待 trace_start() 才开始写入
        std::cout << "[Trace] 波形就绪（暂停）：" << vcd_path
                  << "  输入 'wave start' 开始录制" << std::endl;
    }
}

void Core::close_trace() {
    trace_enabled_ = false;
    if (tfp_) {
        tfp_->close();
        delete tfp_;
        tfp_ = nullptr;
    }
}

void Core::trace_start() noexcept {
    if (!tfp_) {
        std::cerr << "[Trace] 请先与 --wave 参数指定 VCD 路径再开启录制" << std::endl;
        return;
    }
    trace_enabled_ = true;
    std::cout << "[Trace] 录制开始 (t=" << contextp->time() << ")" << std::endl;
}

void Core::trace_stop() noexcept {
    if (trace_enabled_) {
        trace_enabled_ = false;
        // 主动 flush，确保当前波形段落落盘
        if (tfp_) tfp_->flush();
        std::cout << "[Trace] 录制暂停 (t=" << contextp->time() << ")" << std::endl;
    }
}

bool Core::is_tracing() const noexcept {
    return tfp_ != nullptr && trace_enabled_;
}

void Core::eval() {
    top->eval();
    // 双重检查：只有文件就绪且录制开关为开时才写入
    if (tfp_ && trace_enabled_) tfp_->dump(contextp->time());
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

uint32_t Core::get_commit_inst() const {
    return top->io_commit_inst;
}

bool Core::is_commit_store() const {
    return top->io_commit_is_store;
}

bool Core::is_commit_halt() const {
    return top->io_commit_halt;
}

uint32_t Core::get_commit_csr_waddr() const {
    return top->io_commit_csr_waddr;
}

uint32_t Core::get_commit_csr_wdata() const {
    return top->io_commit_csr_wdata;
}

bool Core::is_commit_csr_wen() const {
    return top->io_commit_csr_wen;
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