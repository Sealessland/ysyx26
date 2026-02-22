#include "sEMU/utils/elf_loader.hpp"
#include "sEMU/mem.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <elf.h>

bool ElfLoader::load(const std::string& path, guest_mem& mem) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open ELF file: " << path << "\n";
        return false;
    }
    
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<char> buf(size);
    if (!file.read(buf.data(), size)) {
        std::cerr << "Failed to read ELF file: " << path << "\n";
        return false;
    }
    
    Elf32_Ehdr* ehdr = reinterpret_cast<Elf32_Ehdr*>(buf.data());
    // 检查是否是有效的 ELF 文件
    if (std::memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0) {
        std::cerr << "Invalid ELF Magic.\n";
        return false;
    }
    
    // 加载 LOAD 段
    Elf32_Phdr* phdr = reinterpret_cast<Elf32_Phdr*>(buf.data() + ehdr->e_phoff);
    for (int i = 0; i < ehdr->e_phnum; ++i) {
        if (phdr[i].p_type == PT_LOAD && phdr[i].p_memsz > 0) {
            mem.load_binary(phdr[i].p_paddr, buf.data() + phdr[i].p_offset, phdr[i].p_filesz);
            // 这里暂且不处理 .bss 段（p_memsz > p_filesz 的全 0 部分），假设 mem 已清零
        }
    }
    
    // 解析 Section Headers 找符号表
    Elf32_Shdr* shdr = reinterpret_cast<Elf32_Shdr*>(buf.data() + ehdr->e_shoff);
    for (int i = 0; i < ehdr->e_shnum; ++i) {
        if (shdr[i].sh_type == SHT_SYMTAB) {
            Elf32_Sym* sym_table = reinterpret_cast<Elf32_Sym*>(buf.data() + shdr[i].sh_offset);
            int sym_num = shdr[i].sh_size / sizeof(Elf32_Sym);
            
            Elf32_Shdr* strtab_sec = &shdr[shdr[i].sh_link];
            const char* strtab = buf.data() + strtab_sec->sh_offset;
            
            for (int k = 0; k < sym_num; ++k) {
                if (sym_table[k].st_name != 0) {
                    std::string name = strtab + sym_table[k].st_name;
                    symbol_table[name] = sym_table[k].st_value;
                }
            }
        }
    }
    
    std::cout << "Successfully loaded ELF image and parsed " << symbol_table.size() << " symbols.\n";
    return true;
}

uint32_t ElfLoader::get_symbol_addr(const std::string& name) const {
    auto it = symbol_table.find(name);
    return it != symbol_table.end() ? it->second : 0;
}
