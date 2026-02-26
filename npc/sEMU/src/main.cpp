#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <getopt.h> // 用于命令行参数解析
#include "sEMU/container.hpp"
#include "sEMU/mem.hpp"
#include "sEMU/core.hpp"
#include "sEMU/sdb.hpp"
#include "sEMU/utils/elf_loader.hpp"
#ifdef CONFIG_DIFFTEST
#include "sEMU/difftest.hpp"
#endif
#include "sEMU/utils/colors.hpp"

struct sEMU_Options {
    std::string bin_file;
    std::string elf_file;
    // 未来可以扩展更多的参数，比如 --memory-size, --base-addr 等
};

sEMU_Options parse_args(int argc, char* argv[]) {
    sEMU_Options opt;

    const struct option table[] = {
        {"bin" , required_argument, NULL, 'b'},
        {"elf" , required_argument, NULL, 'e'},
        {"help", no_argument,       NULL, 'h'},
        {0     , 0,                 NULL,  0 }
    };

    int o;
    while ((o = getopt_long(argc, argv, "-hb:e:", table, NULL)) != -1) {
        switch (o) {
            case 'b': opt.bin_file = optarg; break;
            case 'e': opt.elf_file = optarg; break;
            case 'h':
                std::cout << "Usage: " << argv[0] << " [options] [image.bin]\n"
                          << "Options:\n"
                          << "  -b, --bin <file>   Load binary image.\n"
                          << "  -e, --elf <file>   Load ELF image and parse symbols.\n"
                          << "  -h, --help         Show this help message.\n";
                exit(0);
            case 1: 
                if (opt.bin_file.empty() && opt.elf_file.empty()) {
                    // Try to guess by extension or just default to bin
                    std::string arg = optarg;
                    if (arg.length() > 4 && arg.substr(arg.length() - 4) == ".elf") {
                        opt.elf_file = arg;
                    } else {
                        opt.bin_file = arg; 
                    }
                }
                break;
            default:
                std::cerr << ANSI_COLOR_RED << "Unknown argument! Try --help for more information.\n" << ANSI_COLOR_RESET;
                exit(1);
        }
    }
    return opt;
}

int main(int argc, char* argv[]) {
    // 1. 解析参数
    sEMU_Options options = parse_args(argc, argv);

    // 2. 初始化你的虚拟机核心组件
    guest_mem mem; 
    ElfLoader elf_loader;
    bool has_loader = false;
    
    // 优先尝试加载 ELF 文件
    if (!options.elf_file.empty()) {
        std::cout << ANSI_COLOR_GREEN << "Loading ELF image: " << options.elf_file << ANSI_COLOR_RESET << std::endl;
        has_loader = elf_loader.load(options.elf_file, mem);
        if (!has_loader) {
            std::cerr << ANSI_COLOR_RED << "Failed to load ELF image." << ANSI_COLOR_RESET << std::endl;
            return 1;
        }
    } 
    // 退化到直接加载二进制 BIN 文件
    else if (!options.bin_file.empty()) {
        std::cout << ANSI_COLOR_GREEN << "Loading binary image: " << options.bin_file << ANSI_COLOR_RESET << std::endl;
        
        std::ifstream file(options.bin_file, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            std::cerr << ANSI_COLOR_RED << "Failed to open image: " << options.bin_file << ANSI_COLOR_RESET << std::endl;
            return 1;
        }
        
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        std::vector<char> buffer(size);
        if (file.read(buffer.data(), size)) {
            mem.load_binary(0x80000000, buffer.data(), size);
#ifdef CONFIG_DIFFTEST
            difftest.sync_memory(0x80000000, buffer.data(), size, true);
#endif
            std::cout << ANSI_COLOR_GREEN << "Successfully loaded " << size << " bytes into memory." << ANSI_COLOR_RESET << std::endl;
        }
    } 
    // 没有输入时使用硬编码测试序列
    else {
        std::cout << ANSI_COLOR_YELLOW << "No initialization image specified. Booting with a hardcoded test sequence..." << ANSI_COLOR_RESET << std::endl;
        mem.mem_init();
#ifdef CONFIG_DIFFTEST
        // Sync the hardcoded test sequence to REF
        // Note: We need to sync after mem_init() but before difftest.init()
        // For now, we'll sync after difftest.init() in the next section
#endif
    }

    // 初始化处理器核心，并传入内存指针以供 DPI-C 操作
    Core core(&mem);

    // 进行简单的系统复位
    core.reset(5);

#ifdef CONFIG_DIFFTEST
#ifndef DIFFTEST_REF_PATH
#define DIFFTEST_REF_PATH "/home/sealessland/ysyx-workbench/nemu/build/riscv32-nemu-interpreter-so"
#endif
    difftest.init(DIFFTEST_REF_PATH, 0);

    // Always sync memory to REF after loading any image
    // This ensures DUT and REF start with the same memory contents
    size_t sync_size = 128 * 1024 * 1024;  // Sync entire 128MB memory
    difftest.sync_memory(0x80000000, mem.get_host_ptr(0x80000000), sync_size, true);

    // Sync registers to REF
    difftest.sync_registers(&core, true);
#endif

    SDB sdb(&core, &mem, has_loader ? &elf_loader : nullptr);
    sdb.sdb_mainloop();

    return 0;
}
