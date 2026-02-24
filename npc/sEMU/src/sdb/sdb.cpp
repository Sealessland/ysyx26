#include "sEMU/sdb.hpp"
#include "sEMU/core.hpp"
#include "sEMU/mem.hpp"
#include "sEMU/wrapper.hpp"
#include "sEMU/utils/elf_loader.hpp"
#ifdef CONFIG_DIFFTEST
#include "sEMU/difftest.hpp"
#endif
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>

SDB::SDB(Core* core, guest_mem* mem, ElfLoader* loader) : core(core), mem(mem), elf_loader(loader) {
}

SDB::~SDB() {}

static std::vector<std::string> split_args(const std::string& line) {
    std::vector<std::string> args;
    std::istringstream iss(line);
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    return args;
}

void SDB::cmd_c(const std::vector<std::string>& args) {
    (void)args;
    core->state = CoreState::RUNNING;
    // 持续运行直到遇到程序退出点 (比如 ebreak 里修改了 state)
    while (core->state == CoreState::RUNNING) {
        core->step();
    }
    if (core->state == CoreState::END) {
        std::cout << "Program execution has ended (EBREAK)." << std::endl;
    }
}

void SDB::cmd_q(const std::vector<std::string>& args) {
    (void)args;
    std::exit(0);
}

extern bool g_trace_mem;
extern std::vector<std::string> mem_access_log;

void SDB::cmd_si(const std::vector<std::string>& args) {
    int steps = 1;
    std::string mode = "bare"; // 默认使用 bare-metal

    if (!args.empty()) {
        try { steps = std::stoi(args[0]); }
        catch (...) { std::cout << "Invalid argument: " << args[0] << std::endl; return; }
    }
    if (args.size() > 1) {
        mode = args[1];
    }

    core->state = CoreState::RUNNING;
    CoreSimRange sim_range(core);
    int count = 0;

    auto check_limit = [&]() {
        if (++count >= steps) {
            core->state = CoreState::STOPPED;
        }
    };

    if (mode == "bare") {
        g_trace_mem = false;
        run_simulation(sim_range, [&](const CoreCommitState& state) {
            check_limit();
        });
    } 
    else if (mode == "trace") {
        g_trace_mem = true;
        mem_access_log.clear(); // 清理旧日志
        
        run_simulation(sim_range, [&](const CoreCommitState& state) {
            if (state.is_commit_valid()) {
                std::cout << "======================================\n";
                std::cout << "[Trace] PC: 0x" << std::hex << state.get_commit_pc() << std::dec << "\n";
                // 打印所有寄存器
                state.get_core()->print_registers();
                // 打印这周期发生的访存行为
                for (const auto& log : mem_access_log) {
                    std::cout << "[Mem] " << log << "\n";
                }
            }
            mem_access_log.clear();
            check_limit();
        });
        g_trace_mem = false;
    } 
    else if (mode == "diff") {
        g_trace_mem = false;
#ifdef CONFIG_DIFFTEST
        int commit_count = 0;
        bool check_pending = false;
        CPU_state dut_state_to_check;

        run_simulation(sim_range, [&](const CoreCommitState& state) {
            // If we have a pending check, do it now (PC and registers should be updated)
            if (check_pending) {
                // Get the updated DUT state
                for (int i = 0; i < 32; ++i) {
                    dut_state_to_check.gpr[i] = state.get_core()->get_reg(i);
                }
                dut_state_to_check.pc = state.get_core()->get_reg_by_name("pc");

                // Check if DUT and REF match
                if (!difftest.check_registers(dut_state_to_check)) {
                    const_cast<Core*>(state.get_core())->state = CoreState::STOPPED;
                }
                check_pending = false;
            }

            // When DUT commits an instruction
            if (state.is_commit_valid() && !check_pending && state.get_core()->state == CoreState::RUNNING) {
                // Step REF by 1 instruction
                difftest.step(1);

                // Build DUT state using commit signals for register writeback
                for (int i = 0; i < 32; ++i) {
                    dut_state_to_check.gpr[i] = state.get_core()->get_reg(i);
                }

                // If this instruction writes to a register, update it with the commit data
                if (state.get_core()->is_commit_wen()) {
                    uint8_t rd = state.get_core()->get_commit_rd();
                    uint32_t wdata = state.get_core()->get_commit_wdata();
                    if (rd != 0) {  // x0 is always 0
                        dut_state_to_check.gpr[rd] = wdata;
                    }
                }

                // PC will be checked in the next cycle after it updates
                // Schedule check on next cycle
                check_pending = true;

                // Count commits
                if (++commit_count >= steps) {
                    // Don't stop immediately, let the PC update
                }
            }

            // Stop after we've committed and checked all instructions
            if (commit_count >= steps && !check_pending) {
                const_cast<Core*>(state.get_core())->state = CoreState::STOPPED;
            }
        });

        // If we finished with a pending check, do one final check
        if (check_pending) {
            // Step the simulation one more time to let PC update
            run_simulation(sim_range, [&](const CoreCommitState& state) {
                for (int i = 0; i < 32; ++i) {
                    dut_state_to_check.gpr[i] = state.get_core()->get_reg(i);
                }
                dut_state_to_check.pc = state.get_core()->get_reg_by_name("pc");
                difftest.check_registers(dut_state_to_check);
                const_cast<Core*>(state.get_core())->state = CoreState::STOPPED;
            });
        }
#else
        run_simulation(sim_range, [&](const CoreCommitState& state) {
            std::cout << "[Difftest] Disabled during compilation (CONFIG_DIFFTEST not defined).\n";
            const_cast<Core*>(state.get_core())->state = CoreState::STOPPED;
        });
#endif
    }
    else {
        std::cout << "Unknown mode: " << mode << ". Please use 'bare', 'trace', or 'diff'.\n";
        core->state = CoreState::STOPPED;
        return;
    }

    if (core->state == CoreState::END) {
        std::cout << "Program execution has ended (EBREAK)." << std::endl;
    } else {
        std::cout << "Execution paused at PC: 0x" << std::hex << core->get_commit_pc() << std::dec << " after " << steps << " steps." << std::endl;
    }
}

void SDB::cmd_info(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Missing argument for info" << std::endl;
        return;
    }
    if (args[0] == "r") {
        core->print_registers();
    } else if (args[0] == "w") {
        std::cout << "Watchpoint info not implemented yet." << std::endl;
    } else if (args[0] == "func") {
        if (args.size() < 2) {
            std::cout << "Missing function name (Usage: info func <name>)" << std::endl;
        } else if (!elf_loader) {
            std::cout << "No ELF loaded. Cannot resolve symbols." << std::endl;
        } else {
            uint32_t addr = elf_loader->get_symbol_addr(args[1]);
            if (addr != 0) {
                std::cout << "Function '" << args[1] << "' is at address: 0x" << std::hex << addr << std::dec << std::endl;
            } else {
                std::cout << "Function '" << args[1] << "' not found in symbol table." << std::endl;
            }
        }
    } else {
        std::cout << "Unknown info sub-command: " << args[0] << std::endl;
    }
}

void SDB::cmd_x(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: x N EXPR" << std::endl;
        return;
    }
    int n;
    try {
        n = std::stoi(args[0]);
    } catch (...) {
        std::cout << "Invalid number: " << args[0] << std::endl;
        return;
    }

    std::string expr = args[1];
    uint32_t base_addr = 0;
    
    // 简单解析：寄存器值 ($) 或者 十六进制/十进制数值
    try {
        if (expr[0] == '$') {
            std::string reg_name = expr.substr(1);
            base_addr = core->get_reg_by_name(reg_name);
        } else {
            base_addr = std::stoul(expr, nullptr, 0); // 支持0x...和十进制
        }
    } catch (...) {
        std::cout << "Invalid EXPR: " << expr << std::endl;
        return;
    }
    
    for (int i = 0; i < n; ++i) {
        if (i % 4 == 0) {
            std::cout << "0x" << std::hex << std::setw(8) << std::setfill('0') << (base_addr + i * 4) << ": ";
        }
        uint32_t val = mem->lw(base_addr + i * 4);
        std::cout << "0x" << std::hex << std::setw(8) << std::setfill('0') << val << " ";
        if (i % 4 == 3) std::cout << std::endl;
    }
    if (n % 4 != 0) std::cout << std::endl;
    std::cout << std::dec;
}

class AutoTraceAction {
private:
    uint32_t target_func_addr;
    uint32_t target_return_addr = 0;
    bool is_tracing = false;

public:
    uint64_t count = 0;
    uint64_t max_steps;
    CoreState* global_state_ptr;

    AutoTraceAction(uint32_t func_addr, uint64_t steps, CoreState* state_ptr) 
        : target_func_addr(func_addr), max_steps(steps), global_state_ptr(state_ptr) {}

    inline void operator()(const CoreCommitState& state) {
        if (++count > max_steps && !is_tracing) {
            *global_state_ptr = CoreState::STOPPED;
            return;
        }

        if (!state.is_commit_valid()) {
            return;
        }
        
        uint32_t current_pc = state.get_commit_pc();

        if (!is_tracing && current_pc == target_func_addr) {
            is_tracing = true;
            target_return_addr = state.get_reg_by_name("ra"); 
            std::cout << "\n[AutoTrace] Entered target function! Switching to TRACE mode...\n";
            g_trace_mem = true; 
        }
        
        if (is_tracing && current_pc == target_return_addr) {
            is_tracing = false;
            g_trace_mem = false;
            std::cout << "[AutoTrace] Exited target function! Returning to BARE mode...\n\n";
            *global_state_ptr = CoreState::STOPPED; 
        }

        if (is_tracing) {
            std::cout << "======================================\n";
            std::cout << "[Trace] PC: 0x" << std::hex << current_pc << std::dec << "\n";
            state.get_core()->print_registers();
            for (const auto& log : mem_access_log) {
                std::cout << "[Mem] " << log << "\n";
            }
        }
        mem_access_log.clear();
    }
};

void SDB::cmd_trace_func(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Usage: trace-func <function_name>\n";
        return;
    }
    if (!elf_loader) {
        std::cout << "No ELF loaded. Cannot resolve symbols.\n";
        return;
    }
    
    std::string func_name = args[0];
    uint32_t func_addr = elf_loader->get_symbol_addr(func_name);
    if (func_addr == 0) {
        std::cout << "Function '" << func_name << "' not found in ELF symbol table.\n";
        return;
    }
    
    std::cout << "Tracing function '" << func_name << "' at 0x" << std::hex << func_addr << std::dec << "...\n";
    core->state = CoreState::RUNNING;
    CoreSimRange sim_range(core);
    
    g_trace_mem = false;
    mem_access_log.clear();

    AutoTraceAction action(func_addr, 500000000ULL, &core->state);
    run_simulation(sim_range, action);

    if (core->state == CoreState::END) {
        std::cout << "Program execution has ended (EBREAK).\n";
    }
    g_trace_mem = false;
}

void SDB::cmd_help(const std::vector<std::string>& args) {
    (void)args;
    std::cout << "help - Print help information\n"
              << "c - Continue running\n"
              << "q - Quit NEMU\n"
              << "si [N] [mode] - Single step N instructions with optional mode ['bare', 'trace', 'diff'] (default: bare)\n"
              << "trace-func FUNC_NAME - Auto trace when entering and exiting specific function\n"
              << "info SUBCMD - info r (registers), info w (watchpoints), info func FUNC_NAME (get function address)\n"
              << "x N EXPR - Examine memory\n";
}

void SDB::sdb_mainloop() {
    char* line_read;
    while ((line_read = readline("(sEMU) ")) != nullptr) {
        if (line_read && *line_read) {
            add_history(line_read);
            std::string line(line_read);
            auto args = split_args(line);
            if (args.empty()) {
                free(line_read);
                continue;
            }
            std::string cmd = args[0];
            args.erase(args.begin());

            if (cmd == "c") cmd_c(args);
            else if (cmd == "q") cmd_q(args);
            else if (cmd == "si") cmd_si(args);
            else if (cmd == "info") cmd_info(args);
            else if (cmd == "x") cmd_x(args);
            else if (cmd == "trace-func") cmd_trace_func(args);
            else if (cmd == "help") cmd_help(args);
            else std::cout << "Unknown command: " << cmd << std::endl;
        }
        free(line_read);
    }
}
