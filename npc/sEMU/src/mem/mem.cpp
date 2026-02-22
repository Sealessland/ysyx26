#include "sEMU/mem.hpp"
#include <stdexcept>
#include <cstring>

guest_mem::guest_mem(size_t base, size_t sz) 
    : base_addr(base), size(sz) 
{
    mem.resize(sz, 0);
}

uint8_t* guest_mem::get_host_ptr(size_t addr) {
    // if (addr < base_addr || addr >= base_addr + size) { throw std::out_of_range("Memory access out of bounds"); }
    return mem.data() + (addr - base_addr);
}

void guest_mem::load_binary(size_t load_addr, const void* ext_mem, size_t ext_size) {
    std::memcpy(get_host_ptr(load_addr), ext_mem, ext_size);
}

int8_t guest_mem::lb(size_t addr) {
    return *reinterpret_cast<int8_t*>(get_host_ptr(addr));
}

uint8_t guest_mem::lbu(size_t addr) {
    return *reinterpret_cast<uint8_t*>(get_host_ptr(addr));
}

int16_t guest_mem::lh(size_t addr) {
    return *reinterpret_cast<int16_t*>(get_host_ptr(addr));
}

uint16_t guest_mem::lhu(size_t addr) {
    return *reinterpret_cast<uint16_t*>(get_host_ptr(addr));
}

int32_t guest_mem::lw(size_t addr) {
    return *reinterpret_cast<int32_t*>(get_host_ptr(addr));
}

uint32_t guest_mem::lwu(size_t addr) {
    return *reinterpret_cast<uint32_t*>(get_host_ptr(addr));
}

int64_t guest_mem::ld(size_t addr) {
    return *reinterpret_cast<int64_t*>(get_host_ptr(addr));
}

void guest_mem::sb(size_t addr, uint8_t val) {
    *reinterpret_cast<uint8_t*>(get_host_ptr(addr)) = val;
}

void guest_mem::sh(size_t addr, uint16_t val) {
    *reinterpret_cast<uint16_t*>(get_host_ptr(addr)) = val;
}

void guest_mem::sw(size_t addr, uint32_t val) {
    *reinterpret_cast<uint32_t*>(get_host_ptr(addr)) = val;
}

void guest_mem::sd(size_t addr, uint64_t val) {
    *reinterpret_cast<uint64_t*>(get_host_ptr(addr)) = val;
}

uint8_t guest_mem::read_byte(size_t addr) {
    return *get_host_ptr(addr);
}

void guest_mem::write_byte(size_t addr, uint8_t val) {
    *get_host_ptr(addr) = val;
}   

void guest_mem::mem_init(){
    // 提供一段稍微具有复杂度的硬编码指令作为测试
    // 进行算术、访存及分支判断从而考验所有的控制与数据流
    //
    // [0x80000000] 0x00000517 : auipc a0, 0        (a0 = pc = 0x80000000)
    // [0x80000004] 0x00100593 : addi  a1, x0, 1    (a1 = 1)
    // [0x80000008] 0x10b52023 : sw    a1, 256(a0)  (mem[0x80000100] = 1)
    // [0x8000000c] 0x01052603 : lw    a2, 256(a0)  (a2 = mem[0x80000100] = 1)
    // [0x80000010] 0x00c59463 : bne   a1, a2, 8    (if a1 != a2, jump to 0x80000018, skip ebreak)
    // [0x80000014] 0x00100073 : ebreak             (Should hit this and stop gracefully)
    // [0x80000018] 0x0000006f : j     0            (Dead loop if difftest or memory read failed)
    
    const uint32_t hardcoded_insts[] = {
        0x00000517, // auipc x10, 0
        0x00100593, // addi  x11, x0, 1
        0x10b52023, // sw    x11, 256(x10)
        0x01052603, // lw    x12, 256(x10)
        0x00c59463, // bne   x11, x12, 8
        0x00100073, // ebreak
        0x0000006f  // j     0
    };
    
    // 将指令加载到起始地址 (base_addr)
    load_binary(base_addr, hardcoded_insts, sizeof(hardcoded_insts));
}