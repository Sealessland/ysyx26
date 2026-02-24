#include "sEMU/mem.hpp"
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <sys/time.h>

static uint64_t boot_time = 0;

static uint64_t get_time_internal() {
    struct timeval now;
    gettimeofday(&now, NULL);
    uint64_t us = now.tv_sec * 1000000ULL + now.tv_usec;
    return us;
}

guest_mem::guest_mem(size_t base, size_t sz) 
    : base_addr(base), size(sz) 
{
    mem.resize(sz, 0);
    boot_time = get_time_internal();
}

uint8_t* guest_mem::get_host_ptr(size_t addr) {
    // if (addr < base_addr || addr >= base_addr + size) { throw std::out_of_range("Memory access out of bounds"); }
    return mem.data() + (addr - base_addr);
}

void guest_mem::load_binary(size_t load_addr, const void* ext_mem, size_t ext_size) {
    if (in_pmem(load_addr) && in_pmem(load_addr + ext_size - 1)) {
        std::memcpy(get_host_ptr(load_addr), ext_mem, ext_size);
    }
}

uint64_t guest_mem::mmio_read(size_t addr, int len) {
    if (addr == RTC_ADDR) {
        uint64_t now = get_time_internal() - boot_time;
        return (uint32_t)now; // lower 32 bit
    } else if (addr == RTC_ADDR + 4) {
        uint64_t now = get_time_internal() - boot_time;
        return (uint32_t)(now >> 32); // higher 32 bit
    } else if (addr == SERIAL_PORT) {
        std::cout << "Serial port read" << std::endl;   
        return 0; // serial port rx not implemented
    } else if (addr == SERIAL_PORT + 5) { // UART Line Status Register
        return 0x60; // Tx Holding Register Empty & Tx Empty
    }
    return 0;
}

void guest_mem::mmio_write(size_t addr, int len, uint64_t data) {
    if (addr == SERIAL_PORT) {
        std::cout << (char)data << std::flush;
    }
}

uint64_t guest_mem::pmem_read(size_t addr, int len) {
    switch (len) {
        case 1: return *reinterpret_cast<uint8_t*>(get_host_ptr(addr));
        case 2: return *reinterpret_cast<uint16_t*>(get_host_ptr(addr));
        case 4: return *reinterpret_cast<uint32_t*>(get_host_ptr(addr));
        case 8: return *reinterpret_cast<uint64_t*>(get_host_ptr(addr));
        default: return 0;
    }
}

void guest_mem::pmem_write(size_t addr, int len, uint64_t data) {
    switch (len) {
        case 1: *reinterpret_cast<uint8_t*>(get_host_ptr(addr)) = (uint8_t)data; break;
        case 2: *reinterpret_cast<uint16_t*>(get_host_ptr(addr)) = (uint16_t)data; break;
        case 4: *reinterpret_cast<uint32_t*>(get_host_ptr(addr)) = (uint32_t)data; break;
        case 8: *reinterpret_cast<uint64_t*>(get_host_ptr(addr)) = data; break;
    }
}

uint64_t guest_mem::paddr_read(size_t addr, int len) {
    if (in_pmem(addr)) {
        return pmem_read(addr, len);
    } else if (in_mmio(addr)) {
        return mmio_read(addr, len);
    }
    return 0;
}

void guest_mem::paddr_write(size_t addr, int len, uint64_t data) {
    if (in_pmem(addr)) {
        pmem_write(addr, len, data);
    } else if (in_mmio(addr)) {
        mmio_write(addr, len, data);
    }
}

int8_t guest_mem::lb(size_t addr)   { return (int8_t)paddr_read(addr, 1); }
uint8_t guest_mem::lbu(size_t addr) { return (uint8_t)paddr_read(addr, 1); }
int16_t guest_mem::lh(size_t addr)  { return (int16_t)paddr_read(addr, 2); }
uint16_t guest_mem::lhu(size_t addr){ return (uint16_t)paddr_read(addr, 2); }
int32_t guest_mem::lw(size_t addr)  { return (int32_t)paddr_read(addr, 4); }
uint32_t guest_mem::lwu(size_t addr){ return (uint32_t)paddr_read(addr, 4); }
int64_t guest_mem::ld(size_t addr)  { return (int64_t)paddr_read(addr, 8); }

void guest_mem::sb(size_t addr, uint8_t val)  { paddr_write(addr, 1, val); }
void guest_mem::sh(size_t addr, uint16_t val) { paddr_write(addr, 2, val); }
void guest_mem::sw(size_t addr, uint32_t val) { paddr_write(addr, 4, val); }
void guest_mem::sd(size_t addr, uint64_t val) { paddr_write(addr, 8, val); }

uint8_t guest_mem::read_byte(size_t addr) { return (uint8_t)paddr_read(addr, 1); }
void guest_mem::write_byte(size_t addr, uint8_t val) { paddr_write(addr, 1, val); }

void guest_mem::mem_init(){
    // 提供一段稍微具有复杂度的硬编码指令作为测试
    // 进行算术、访存及分支判断从而考验所有的控制与数据流
    //
    // 带有设备访存测试的硬编码程序
    // 输出 'd', 'x', 'y', '\n' 到串口
    //
    // lui   a0, 0xa0000     (a0 = 0xa0000000)
    // addi  a0, a0, 0x3f8   (a0 = 0xa00003f8)
    // addi  a1, x0, 100     (a1 = 'd')
    // sb    a1, 0(a0)       (SERIAL_PORT <- 'd')
    // addi  a1, x0, 120     (a1 = 'x')
    // sb    a1, 0(a0)       (SERIAL_PORT <- 'x')
    // addi  a1, x0, 121     (a1 = 'y')
    // sb    a1, 0(a0)       (SERIAL_PORT <- 'y')
    // addi  a1, x0, 10      (a1 = '\n')
    // sb    a1, 0(a0)       (SERIAL_PORT <- '\n')
    // ebreak                (Stop Execution)
    // j     0
    
    const uint32_t hardcoded_insts[] = {
        0xa0000537, // lui   a0, 0xa0000
        0x3f850513, // addi  a0, a0, 0x3f8
        0x06400593, // addi  a1, x0, 100 ('d')
        0x00b50023, // sb    a1, 0(a0)
        0x07800593, // addi  a1, x0, 120 ('x')
        0x00b50023, // sb    a1, 0(a0)
        0x07900593, // addi  a1, x0, 121 ('y')
        0x00b50023, // sb    a1, 0(a0)
        0x00a00593, // addi  a1, x0, 10 ('\n')
        0x00b50023, // sb    a1, 0(a0)
        0x00100073, // ebreak
        0x0000006f  // j     0
    };
    
    // 将指令加载到起始地址 (base_addr)
    load_binary(base_addr, hardcoded_insts, sizeof(hardcoded_insts));
}