#include "VCoreTop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>

namespace {
constexpr uint32_t kBase = 0x80000000u;
constexpr uint32_t kDataBase = 0x80001000u;
constexpr size_t kMemSize = 1 << 16; // 64KB
constexpr uint32_t kCsrMstatus = 0x300;
constexpr uint32_t kCsrMtvec = 0x305;
constexpr uint32_t kCsrMepc = 0x341;
constexpr uint32_t kCsrMcause = 0x342;

std::vector<uint8_t> g_mem(kMemSize, 0);
bool g_ebreak_called = false;

inline bool addr_in_range(uint32_t addr) {
  return addr >= kBase && (addr - kBase) < g_mem.size();
}

inline uint32_t mem_read32_aligned(uint32_t addr) {
  uint32_t base = addr & ~0x3u;
  if (!addr_in_range(base) || !addr_in_range(base + 3)) {
    return 0;
  }
  uint32_t idx = base - kBase;
  return static_cast<uint32_t>(g_mem[idx]) |
         (static_cast<uint32_t>(g_mem[idx + 1]) << 8) |
         (static_cast<uint32_t>(g_mem[idx + 2]) << 16) |
         (static_cast<uint32_t>(g_mem[idx + 3]) << 24);
}

inline void mem_write(uint32_t addr, uint64_t data, uint8_t len) {
  if (!addr_in_range(addr) || !addr_in_range(addr + len - 1)) {
    return;
  }
  uint32_t idx = addr - kBase;
  for (uint8_t i = 0; i < len; ++i) {
    g_mem[idx + i] = static_cast<uint8_t>((data >> (8 * i)) & 0xffu);
  }
}

inline int32_t sign_extend(uint32_t val, int bits) {
  uint32_t m = 1u << (bits - 1);
  return static_cast<int32_t>((val ^ m) - m);
}

constexpr uint32_t encode_r(uint32_t funct7, uint32_t rs2, uint32_t rs1,
                            uint32_t funct3, uint32_t rd, uint32_t opcode) {
  return (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) |
         (rd << 7) | opcode;
}

constexpr uint32_t encode_i(int32_t imm, uint32_t rs1, uint32_t funct3,
                            uint32_t rd, uint32_t opcode) {
  uint32_t uimm = static_cast<uint32_t>(imm) & 0xfff;
  return (uimm << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
}

constexpr uint32_t encode_s(int32_t imm, uint32_t rs2, uint32_t rs1,
                            uint32_t funct3, uint32_t opcode) {
  uint32_t uimm = static_cast<uint32_t>(imm) & 0xfff;
  uint32_t imm_hi = (uimm >> 5) & 0x7f;
  uint32_t imm_lo = uimm & 0x1f;
  return (imm_hi << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) |
         (imm_lo << 7) | opcode;
}

constexpr uint32_t encode_b(int32_t imm, uint32_t rs2, uint32_t rs1,
                            uint32_t funct3, uint32_t opcode) {
  uint32_t uimm = static_cast<uint32_t>(imm) & 0x1fff;
  uint32_t imm12 = (uimm >> 12) & 0x1;
  uint32_t imm11 = (uimm >> 11) & 0x1;
  uint32_t imm10_5 = (uimm >> 5) & 0x3f;
  uint32_t imm4_1 = (uimm >> 1) & 0xf;
  return (imm12 << 31) | (imm10_5 << 25) | (rs2 << 20) | (rs1 << 15) |
         (funct3 << 12) | (imm4_1 << 8) | (imm11 << 7) | opcode;
}

constexpr uint32_t encode_u(uint32_t imm, uint32_t rd, uint32_t opcode) {
  return (imm & 0xfffff000u) | (rd << 7) | opcode;
}

constexpr uint32_t encode_j(int32_t imm, uint32_t rd, uint32_t opcode) {
  uint32_t uimm = static_cast<uint32_t>(imm) & 0x1fffff;
  uint32_t imm20 = (uimm >> 20) & 0x1;
  uint32_t imm19_12 = (uimm >> 12) & 0xff;
  uint32_t imm11 = (uimm >> 11) & 0x1;
  uint32_t imm10_1 = (uimm >> 1) & 0x3ff;
  return (imm20 << 31) | (imm19_12 << 12) | (imm11 << 20) |
         (imm10_1 << 21) | (rd << 7) | opcode;
}

struct CommitExp {
  uint32_t pc;
  uint8_t rd;
  uint32_t wdata;
  bool wen;
};

std::vector<uint32_t> build_program() {
  std::vector<uint32_t> prog;
  prog.reserve(200);

  // Prologue: setup base and registers
  prog.push_back(encode_u(0x80001000u, 10, 0x37)); // lui x10, 0x80001000
  for (uint32_t i = 1; i <= 8; ++i) {
    prog.push_back(encode_i(static_cast<int32_t>(i), 0, 0x0, i, 0x13));
  }
  prog.push_back(encode_i(0x55, 0, 0x0, 9, 0x13));  // addi x9, x0, 0x55
  prog.push_back(encode_i(0xAA, 0, 0x0, 11, 0x13)); // addi x11, x0, 0xAA

  // Word stores/loads at offsets multiple of 8 (addr[2]=0)
  for (uint32_t i = 0; i < 8; ++i) {
    prog.push_back(encode_s(static_cast<int32_t>(i * 8), i + 1, 10, 0x2, 0x23));
  }
  for (uint32_t i = 0; i < 8; ++i) {
    prog.push_back(encode_i(static_cast<int32_t>(i * 8), 10, 0x2, 12 + i, 0x03));
  }

  // Byte/half tests at base+32 (addr[2]=0)
  prog.push_back(encode_i(32, 10, 0x0, 20, 0x13)); // addi x20, x10, 32
  prog.push_back(encode_s(1, 9, 20, 0x0, 0x23));    // sb x9, 1(x20)
  prog.push_back(encode_i(1, 20, 0x0, 13, 0x03));   // lb x13, 1(x20)
  prog.push_back(encode_i(1, 20, 0x4, 14, 0x03));   // lbu x14, 1(x20)
  prog.push_back(encode_s(2, 11, 20, 0x1, 0x23));   // sh x11, 2(x20)
  prog.push_back(encode_i(2, 20, 0x1, 15, 0x03));   // lh x15, 2(x20)
  prog.push_back(encode_i(2, 20, 0x5, 16, 0x03));   // lhu x16, 2(x20)

  // Tricky immediates, sign/zero tests, and shifts
  prog.push_back(encode_i(-1, 0, 0x0, 21, 0x13));      // addi x21, x0, -1
  prog.push_back(encode_i(0x7ff, 0, 0x0, 22, 0x13));   // addi x22, x0, 2047
  prog.push_back(encode_i(-2048, 0, 0x0, 23, 0x13));   // addi x23, x0, -2048
  prog.push_back(encode_u(0x80000000u, 24, 0x37));     // lui x24, 0x80000000
  prog.push_back(encode_i(1, 24, 0x0, 24, 0x13));      // addi x24, x24, 1
  prog.push_back(encode_u(0x80000000u, 25, 0x37));     // lui x25, 0x80000000
  prog.push_back(encode_i(-1, 25, 0x0, 25, 0x13));     // addi x25, x25, -1 -> 0x7fffffff
  prog.push_back(encode_i(0x80, 0, 0x0, 26, 0x13));    // addi x26, x0, 0x80
  prog.push_back(encode_u(0x00008000u, 27, 0x37));     // lui x27, 0x00008000
  prog.push_back(encode_i(1, 27, 0x0, 27, 0x13));      // addi x27, x27, 1 -> 0x8001

  prog.push_back(encode_s(40, 24, 10, 0x2, 0x23));     // sw x24, 40(x10)
  prog.push_back(encode_i(40, 10, 0x2, 28, 0x03));     // lw x28, 40(x10)
  prog.push_back(encode_s(44, 25, 10, 0x2, 0x23));     // sw x25, 44(x10)
  prog.push_back(encode_i(44, 10, 0x2, 29, 0x03));     // lw x29, 44(x10)
  prog.push_back(encode_s(48, 26, 10, 0x0, 0x23));     // sb x26, 48(x10)
  prog.push_back(encode_s(50, 27, 10, 0x1, 0x23));     // sh x27, 50(x10)
  prog.push_back(encode_i(48, 10, 0x0, 30, 0x03));     // lb x30, 48(x10)
  prog.push_back(encode_i(48, 10, 0x4, 31, 0x03));     // lbu x31, 48(x10)
  prog.push_back(encode_i(50, 10, 0x1, 18, 0x03));     // lh x18, 50(x10)
  prog.push_back(encode_i(50, 10, 0x5, 19, 0x03));     // lhu x19, 50(x10)

  prog.push_back(encode_i(0x7ff, 21, 0x7, 17, 0x13));  // andi x17, x21, 0x7ff
  prog.push_back(encode_i(-1, 22, 0x6, 16, 0x13));     // ori  x16, x22, -1
  prog.push_back(encode_i(-1, 22, 0x4, 15, 0x13));     // xori x15, x22, -1
  prog.push_back(encode_i(-1, 23, 0x2, 14, 0x13));     // slti x14, x23, -1
  prog.push_back(encode_i(-1, 23, 0x3, 13, 0x13));     // sltiu x13, x23, -1

  // Skip shift-immediate ops for now (slli/srli/srai).

  // JAL/JALR control flow checks
  prog.push_back(encode_j(8, 6, 0x6f));                // jal x6, +8
  prog.push_back(encode_i(1, 0, 0x0, 7, 0x13));        // addi x7, x0, 1 (skipped)
  prog.push_back(encode_i(2, 0, 0x0, 7, 0x13));        // addi x7, x0, 2
  prog.push_back(encode_u(0x00000000u, 6, 0x17));      // auipc x6, 0
  prog.push_back(encode_i(16, 6, 0x0, 6, 0x13));       // addi x6, x6, 16
  prog.push_back(encode_i(0, 6, 0x0, 8, 0x67));        // jalr x8, 0(x6)
  prog.push_back(encode_i(1, 0, 0x0, 9, 0x13));        // addi x9, x0, 1 (skipped)
  prog.push_back(encode_i(2, 0, 0x0, 9, 0x13));        // addi x9, x0, 2

  // Arithmetic mix loop (110 instructions)
  for (int i = 0; i < 10; ++i) {
    prog.push_back(encode_i(1, 1, 0x0, 1, 0x13));          // addi x1, x1, 1
    prog.push_back(encode_r(0x00, 1, 2, 0x0, 2, 0x33));    // add  x2, x2, x1
    prog.push_back(encode_r(0x20, 1, 3, 0x0, 3, 0x33));    // sub  x3, x3, x1
    prog.push_back(encode_r(0x00, 2, 4, 0x7, 4, 0x33));    // and  x4, x4, x2
    prog.push_back(encode_r(0x00, 3, 5, 0x6, 5, 0x33));    // or   x5, x5, x3
    prog.push_back(encode_r(0x00, 5, 6, 0x4, 6, 0x33));    // xor  x6, x6, x5
    prog.push_back(encode_r(0x00, 1, 7, 0x1, 7, 0x33));    // sll  x7, x7, x1
    prog.push_back(encode_r(0x00, 2, 8, 0x5, 8, 0x33));    // srl  x8, x8, x2
    prog.push_back(encode_r(0x20, 3, 9, 0x5, 9, 0x33));    // sra  x9, x9, x3
    prog.push_back(encode_r(0x00, 2, 1, 0x2, 11, 0x33));   // slt  x11, x1, x2
    prog.push_back(encode_r(0x00, 2, 1, 0x3, 12, 0x33));   // sltu x12, x1, x2
  }

  // Branch edge cases (taken and not taken)
  prog.push_back(encode_i(-1, 0, 0x0, 17, 0x13)); // addi x17, x0, -1
  prog.push_back(encode_i(1, 0, 0x0, 18, 0x13));  // addi x18, x0, 1
  prog.push_back(encode_b(8, 18, 17, 0x4, 0x63)); // blt x17,x18,+8 (taken)
  prog.push_back(encode_i(1, 0, 0x0, 19, 0x13));  // addi x19, x0, 1 (skipped)
  prog.push_back(encode_i(2, 0, 0x0, 19, 0x13));  // addi x19, x0, 2
  prog.push_back(encode_b(8, 18, 17, 0x6, 0x63)); // bltu x17,x18,+8 (not taken)
  prog.push_back(encode_i(3, 0, 0x0, 20, 0x13));  // addi x20, x0, 3
  prog.push_back(encode_i(4, 0, 0x0, 20, 0x13));  // addi x20, x0, 4
  prog.push_back(encode_b(8, 18, 18, 0x1, 0x63)); // bne x18,x18,+8 (not taken)
  prog.push_back(encode_i(5, 0, 0x0, 21, 0x13));  // addi x21, x0, 5
  prog.push_back(encode_b(8, 18, 18, 0x0, 0x63)); // beq x18,x18,+8 (taken)
  prog.push_back(encode_i(6, 0, 0x0, 21, 0x13));  // addi x21, x0, 6 (skipped)
  prog.push_back(encode_i(7, 0, 0x0, 21, 0x13));  // addi x21, x0, 7

  // CSR tests: MSTATUS/MTVEC/MEPC/MCAUSE with six CSR ops.
  prog.push_back(encode_i(0x111, 0, 0x0, 5, 0x13)); // addi x5, x0, 0x111
  prog.push_back(encode_i(0x222, 0, 0x0, 6, 0x13)); // addi x6, x0, 0x222
  prog.push_back(encode_i(0x333, 0, 0x0, 7, 0x13)); // addi x7, x0, 0x333
  prog.push_back(encode_i(0x444, 0, 0x0, 8, 0x13)); // addi x8, x0, 0x444

  // MSTATUS: csrrw/csrrs/csrrc + readback
  prog.push_back(encode_i(kCsrMstatus, 5, 0x1, 20, 0x73)); // csrrw x20, mstatus, x5
  prog.push_back(encode_i(kCsrMstatus, 6, 0x2, 21, 0x73)); // csrrs x21, mstatus, x6
  prog.push_back(encode_i(kCsrMstatus, 5, 0x3, 22, 0x73)); // csrrc x22, mstatus, x5
  prog.push_back(encode_i(kCsrMstatus, 0, 0x2, 23, 0x73)); // csrrs x23, mstatus, x0

  // MTVEC: csrrwi/csrrsi/csrrci + readback
  prog.push_back(encode_i(kCsrMtvec, 0x1f, 0x5, 24, 0x73)); // csrrwi x24, mtvec, 0x1f
  prog.push_back(encode_i(kCsrMtvec, 0x03, 0x6, 25, 0x73)); // csrrsi x25, mtvec, 0x03
  prog.push_back(encode_i(kCsrMtvec, 0x07, 0x7, 26, 0x73)); // csrrci x26, mtvec, 0x07
  prog.push_back(encode_i(kCsrMtvec, 0, 0x2, 27, 0x73));    // csrrs x27, mtvec, x0

  // MEPC: csrrw + readback
  prog.push_back(encode_i(kCsrMepc, 7, 0x1, 28, 0x73)); // csrrw x28, mepc, x7
  prog.push_back(encode_i(kCsrMepc, 0, 0x2, 29, 0x73)); // csrrs x29, mepc, x0

  // MCAUSE: csrrw/csrrc + readback
  prog.push_back(encode_i(kCsrMcause, 8, 0x1, 30, 0x73)); // csrrw x30, mcause, x8
  prog.push_back(encode_i(kCsrMcause, 6, 0x3, 31, 0x73)); // csrrc x31, mcause, x6
  prog.push_back(encode_i(kCsrMcause, 0, 0x2, 18, 0x73)); // csrrs x18, mcause, x0

  // Terminate
  prog.push_back(0x00100073u); // ebreak

  return prog;
}

std::vector<CommitExp> run_reference(const std::vector<uint32_t> &prog) {
  std::vector<CommitExp> commits;
  uint32_t pc = kBase;
  uint32_t regs[32] = {0};
  uint32_t mstatus = 0;
  uint32_t mtvec = 0;
  uint32_t mepc = 0;
  uint32_t mcause = 0;

  auto csr_read = [&](uint32_t addr) -> uint32_t {
    switch (addr) {
    case kCsrMstatus: return mstatus;
    case kCsrMtvec: return mtvec;
    case kCsrMepc: return mepc;
    case kCsrMcause: return mcause;
    default: return 0;
    }
  };

  auto csr_write = [&](uint32_t addr, uint32_t val) {
    switch (addr) {
    case kCsrMstatus: mstatus = val; break;
    case kCsrMtvec: mtvec = val; break;
    case kCsrMepc: mepc = val; break;
    case kCsrMcause: mcause = val; break;
    default: break;
    }
  };

  auto load_u8 = [&](uint32_t addr) -> uint8_t {
    if (!addr_in_range(addr)) return 0;
    return g_mem[addr - kBase];
  };

  auto load_u16 = [&](uint32_t addr) -> uint16_t {
    return static_cast<uint16_t>(load_u8(addr)) |
           (static_cast<uint16_t>(load_u8(addr + 1)) << 8);
  };

  auto load_u32 = [&](uint32_t addr) -> uint32_t {
    return static_cast<uint32_t>(load_u8(addr)) |
           (static_cast<uint32_t>(load_u8(addr + 1)) << 8) |
           (static_cast<uint32_t>(load_u8(addr + 2)) << 16) |
           (static_cast<uint32_t>(load_u8(addr + 3)) << 24);
  };

  for (size_t steps = 0; steps < 10000; ++steps) {
    uint32_t idx = (pc - kBase) >> 2;
    if (idx >= prog.size()) {
      break;
    }
    uint32_t inst = prog[idx];

    uint32_t opcode = inst & 0x7f;
    uint32_t rd = (inst >> 7) & 0x1f;
    uint32_t funct3 = (inst >> 12) & 0x7;
    uint32_t rs1 = (inst >> 15) & 0x1f;
    uint32_t rs2 = (inst >> 20) & 0x1f;
    uint32_t funct7 = (inst >> 25) & 0x7f;

    int32_t imm_i = sign_extend(inst >> 20, 12);
    int32_t imm_s = sign_extend(((inst >> 25) << 5) | ((inst >> 7) & 0x1f), 12);
    int32_t imm_b = sign_extend(
        ((inst >> 31) << 12) | (((inst >> 7) & 0x1) << 11) |
            (((inst >> 25) & 0x3f) << 5) | (((inst >> 8) & 0xf) << 1),
        13);
    int32_t imm_j = sign_extend(
        ((inst >> 31) << 20) | (((inst >> 12) & 0xff) << 12) |
            (((inst >> 20) & 0x1) << 11) | (((inst >> 21) & 0x3ff) << 1),
        21);
    uint32_t imm_u = inst & 0xfffff000u;

    uint32_t next_pc = pc + 4;
    bool wen = false;
    uint32_t wdata = 0;

    switch (opcode) {
    case 0x37: // LUI
      wdata = imm_u;
      wen = true;
      break;
    case 0x17: // AUIPC
      wdata = pc + imm_u;
      wen = true;
      break;
    case 0x6f: // JAL
      wdata = pc + 4;
      wen = true;
      next_pc = pc + imm_j;
      break;
    case 0x67: // JALR
      wdata = pc + 4;
      wen = true;
      next_pc = (regs[rs1] + imm_i) & ~1u;
      break;
    case 0x63: { // BRANCH
      uint32_t a = regs[rs1];
      uint32_t b = regs[rs2];
      bool take = false;
      switch (funct3) {
      case 0x0: take = (a == b); break; // beq
      case 0x1: take = (a != b); break; // bne
      case 0x4: take = (static_cast<int32_t>(a) < static_cast<int32_t>(b)); break; // blt
      case 0x5: take = (static_cast<int32_t>(a) >= static_cast<int32_t>(b)); break; // bge
      case 0x6: take = (a < b); break; // bltu
      case 0x7: take = (a >= b); break; // bgeu
      default: break;
      }
      if (take) next_pc = pc + imm_b;
      break;
    }
    case 0x03: { // LOAD
      uint32_t addr = regs[rs1] + imm_i;
      uint32_t raw = mem_read32_aligned(addr);
      uint32_t shift = (addr & 0x3u) * 8;
      uint32_t shifted = raw >> shift;
      switch (funct3) {
      case 0x0: wdata = static_cast<uint32_t>(sign_extend(shifted & 0xff, 8)); break; // lb
      case 0x1: wdata = static_cast<uint32_t>(sign_extend(shifted & 0xffff, 16)); break; // lh
      case 0x2: wdata = shifted; break; // lw
      case 0x4: wdata = shifted & 0xff; break; // lbu
      case 0x5: wdata = shifted & 0xffff; break; // lhu
      default: wdata = 0; break;
      }
      wen = true;
      break;
    }
    case 0x23: { // STORE
      uint32_t addr = regs[rs1] + imm_s;
      uint32_t data = regs[rs2];
      switch (funct3) {
      case 0x0: mem_write(addr, data & 0xffu, 1); break; // sb
      case 0x1: mem_write(addr, data & 0xffffu, 2); break; // sh
      case 0x2: mem_write(addr, data, 4); break; // sw
      default: break;
      }
      break;
    }
    case 0x13: { // OP-IMM
      uint32_t a = regs[rs1];
      switch (funct3) {
      case 0x0: wdata = a + imm_i; break; // addi
      case 0x2: wdata = (static_cast<int32_t>(a) < imm_i) ? 1 : 0; break; // slti
      case 0x3: wdata = (a < static_cast<uint32_t>(imm_i)) ? 1 : 0; break; // sltiu
      case 0x4: wdata = a ^ static_cast<uint32_t>(imm_i); break; // xori
      case 0x6: wdata = a | static_cast<uint32_t>(imm_i); break; // ori
      case 0x7: wdata = a & static_cast<uint32_t>(imm_i); break; // andi
      case 0x1: wdata = a << (imm_i & 0x1f); break; // slli
      case 0x5:
        if ((imm_i & 0xfe0) == 0x400) {
          wdata = static_cast<uint32_t>(static_cast<int32_t>(a) >> (imm_i & 0x1f)); // srai
        } else {
          wdata = a >> (imm_i & 0x1f); // srli
        }
        break;
      default: wdata = 0; break;
      }
      wen = true;
      break;
    }
    case 0x33: { // OP
      uint32_t a = regs[rs1];
      uint32_t b = regs[rs2];
      switch (funct3) {
      case 0x0: wdata = (funct7 == 0x20) ? a - b : a + b; break; // add/sub
      case 0x1: wdata = a << (b & 0x1f); break; // sll
      case 0x2: wdata = (static_cast<int32_t>(a) < static_cast<int32_t>(b)) ? 1 : 0; break; // slt
      case 0x3: wdata = (a < b) ? 1 : 0; break; // sltu
      case 0x4: wdata = a ^ b; break; // xor
      case 0x5:
        if (funct7 == 0x20) {
          wdata = static_cast<uint32_t>(static_cast<int32_t>(a) >> (b & 0x1f));
        } else {
          wdata = a >> (b & 0x1f);
        }
        break;
      case 0x6: wdata = a | b; break; // or
      case 0x7: wdata = a & b; break; // and
      default: wdata = 0; break;
      }
      wen = true;
      break;
    }
    case 0x73: { // SYSTEM/CSR
      if (funct3 == 0x0) {
        if (inst == 0x00100073u) {
          // ebreak
          commits.push_back({pc, 0, 0, false});
          return commits;
        }
        break;
      }

      uint32_t csr_addr = (inst >> 20) & 0xfff;
      uint32_t old_val = csr_read(csr_addr);
      uint32_t src = ((funct3 & 0x4) != 0) ? static_cast<uint32_t>(rs1)
                                           : regs[rs1];
      uint32_t new_val = old_val;
      bool do_write = true;

      switch (funct3) {
      case 0x1: new_val = src; break;               // csrrw
      case 0x2: new_val = old_val | src; break;     // csrrs
      case 0x3: new_val = old_val & ~src; break;    // csrrc
      case 0x5: new_val = src; break;               // csrrwi
      case 0x6: new_val = old_val | src; break;     // csrrsi
      case 0x7: new_val = old_val & ~src; break;    // csrrci
      default: do_write = false; break;
      }

      if (funct3 == 0x2 || funct3 == 0x3 || funct3 == 0x6 || funct3 == 0x7) {
        if (rs1 == 0) {
          do_write = false; // CSRRS/CSRRC with rs1/zimm=0 are read-only.
        }
      }

      if (do_write) {
        csr_write(csr_addr, new_val);
      }

      wdata = old_val;
      wen = (rd != 0);
      break;
    }
    default:
      break;
    }

    if (wen && rd != 0) {
      regs[rd] = wdata;
    }

    commits.push_back({pc, static_cast<uint8_t>(rd), wdata, wen && rd != 0});
    regs[0] = 0;
    pc = next_pc;
  }

  return commits;
}

void load_program(const std::vector<uint32_t> &prog) {
  for (size_t i = 0; i < prog.size(); ++i) {
    uint32_t addr = kBase + static_cast<uint32_t>(i * 4);
    if (!addr_in_range(addr + 3)) {
      break;
    }
    uint32_t idx = addr - kBase;
    g_mem[idx] = static_cast<uint8_t>(prog[i] & 0xffu);
    g_mem[idx + 1] = static_cast<uint8_t>((prog[i] >> 8) & 0xffu);
    g_mem[idx + 2] = static_cast<uint8_t>((prog[i] >> 16) & 0xffu);
    g_mem[idx + 3] = static_cast<uint8_t>((prog[i] >> 24) & 0xffu);
  }
}

void eval_low(VCoreTop *top, VerilatedContext *ctx, VerilatedVcdC *tfp) {
  top->clock = 0;
  top->eval();
  if (tfp) tfp->dump(ctx->time());
  ctx->timeInc(1);
}

void eval_high(VCoreTop *top, VerilatedContext *ctx, VerilatedVcdC *tfp) {
  top->clock = 1;
  top->eval();
  if (tfp) tfp->dump(ctx->time());
  ctx->timeInc(1);
}
} // namespace

extern "C" int paddr_read(int raddr) {
  uint32_t addr = static_cast<uint32_t>(raddr);
  if (!addr_in_range(addr) || !addr_in_range(addr + 3)) {
    return 0;
  }
  return static_cast<int>(mem_read32_aligned(addr));
}

extern "C" long long pmem_read(long long raddr, unsigned char /*len*/) {
  uint32_t addr = static_cast<uint32_t>(raddr);
  return static_cast<long long>(mem_read32_aligned(addr));
}

extern "C" void pmem_write(long long waddr, long long wdata, unsigned char len) {
  mem_write(static_cast<uint32_t>(waddr), static_cast<uint64_t>(wdata), len);
}

extern "C" void npc_ebreak() { g_ebreak_called = true; }

int main(int argc, char **argv) {
  auto program = build_program();
  load_program(program);
  auto expected = run_reference(program);

  if (program.size() < 100) {
    std::fprintf(stderr, "Program too short: %zu instructions\n", program.size());
    return 1;
  }

  VerilatedContext ctx;
  ctx.commandArgs(argc, argv);
  ctx.traceEverOn(true);

  auto top = std::make_unique<VCoreTop>(&ctx);

  VerilatedVcdC tfp;
  top->trace(&tfp, 20);
  tfp.open("build/verilator/wave.vcd");

  top->clock = 0;
  top->reset = 1;

  // Reset for a few cycles.
  eval_low(top.get(), &ctx, &tfp);
  eval_high(top.get(), &ctx, &tfp);
  eval_low(top.get(), &ctx, &tfp);
  eval_high(top.get(), &ctx, &tfp);
  eval_low(top.get(), &ctx, &tfp);
  eval_high(top.get(), &ctx, &tfp);
  top->reset = 0;

  size_t idx = 0;
  bool started = false;
  int errors = 0;
  const size_t max_cycles = expected.size() + 50;

  for (size_t cycles = 0; cycles < max_cycles; ++cycles) {
    eval_low(top.get(), &ctx, &tfp);
    const uint32_t pc = top->io_commit_pc;
    const bool wen = top->io_commit_wen != 0;

    if (!started) {
      if (pc == expected[0].pc) {
        started = true;
      } else {
        eval_high(top.get(), &ctx, &tfp);
        continue;
      }
    }

    if (idx >= expected.size()) {
      break;
    }

    const auto &exp = expected[idx];
    if (pc != exp.pc) {
      std::fprintf(stderr,
                   "PC mismatch at commit %zu: got 0x%08x expected 0x%08x\n",
                   idx, pc, exp.pc);
      errors++;
      break;
    }
    if (wen != exp.wen) {
      std::fprintf(stderr,
                   "WEN mismatch at pc=0x%08x: got %u expected %u\n", pc,
                   static_cast<uint32_t>(wen), static_cast<uint32_t>(exp.wen));
      errors++;
    }
    if (exp.wen) {
      if (top->io_commit_rd != exp.rd) {
        std::fprintf(stderr,
                     "RD mismatch at pc=0x%08x: got %u expected %u\n", pc,
                     top->io_commit_rd, exp.rd);
        errors++;
      }
      if (top->io_commit_wdata != exp.wdata) {
        std::fprintf(stderr,
                     "WDATA mismatch at pc=0x%08x: got 0x%08x expected 0x%08x\n",
                     pc, top->io_commit_wdata, exp.wdata);
        errors++;
      }
    }

    eval_high(top.get(), &ctx, &tfp);
    idx++;
    if (g_ebreak_called) {
      break;
    }
    if (idx == expected.size()) {
      break;
    }
  }

  top->final();
  tfp.close();

  if (!started) {
    std::fprintf(stderr, "No commits observed.\n");
    return 1;
  }
  if (!g_ebreak_called) {
    std::fprintf(stderr, "Ebreak was not observed.\n");
    return 1;
  }
  if (idx != expected.size()) {
    std::fprintf(stderr, "Only %zu/%zu commits observed.\n", idx, expected.size());
    return 1;
  }
  if (errors != 0) {
    std::fprintf(stderr, "Verification failed with %d errors.\n", errors);
    return 1;
  }

  std::printf("PASS: %zu instructions committed. Waveform: build/verilator/wave.vcd\n",
              expected.size());
  return 0;
}
