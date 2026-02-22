/***************************************************************************************
 * Copyright (c) 2014-2024 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"

#define REGNUM 32

// ANSI Color Codes
#define ANSI_FG_BLACK   "\33[1;30m"
#define ANSI_FG_RED     "\33[1;31m"
#define ANSI_FG_GREEN   "\33[1;32m"
#define ANSI_FG_YELLOW  "\33[1;33m"
#define ANSI_FG_BLUE    "\33[1;34m"
#define ANSI_FG_MAGENTA "\33[1;35m"
#define ANSI_FG_CYAN    "\33[1;36m"
#define ANSI_FG_WHITE   "\33[1;37m"
#define ANSI_BG_BLACK   "\33[1;40m"
#define ANSI_BG_RED     "\33[1;41m"
#define ANSI_BG_GREEN   "\33[1;42m"
#define ANSI_BG_YELLOW  "\33[1;43m"
#define ANSI_BG_BLUE    "\33[1;44m"
#define ANSI_BG_MAGENTA "\33[1;45m"
#define ANSI_BG_CYAN    "\33[1;46m"
#define ANSI_BG_WHITE   "\33[1;47m"
#define ANSI_NONE       "\33[0m"


bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  bool flag = true;
  int i;
  
  // Register mismatch status
  bool reg_mismatch[REGNUM] = {false};
  bool pc_mismatch = false;
  
  // Check PC
  if(ref_r->pc != cpu.pc) {
    flag = false;
    pc_mismatch = true;
    printf("%sPC mismatch: ref_pc=0x%x, dut_pc=0x%x%s\n", 
           ANSI_FG_RED, ref_r->pc, cpu.pc, ANSI_NONE);
  }
  
  // Check GPRs
  for(i = 0; i < REGNUM; i++) {
    if(ref_r->gpr[i] != cpu.gpr[i]) {
      flag = false;
      reg_mismatch[i] = true;
      printf("%sGPR[%s] mismatch: ref=0x%x, dut=0x%x%s\n", 
             ANSI_FG_RED, reg_name(i), ref_r->gpr[i], cpu.gpr[i], ANSI_NONE);
    }
  }
  
  // If mismatch, print details
  if(flag == false) {
    printf("\n=========== Register State Mismatch Details ===========\n");
    
    // Print PC
    printf("PC: ");
    if(pc_mismatch) {
      printf("%sref=0x%08x dut=0x%08x%s\n", 
             ANSI_BG_RED, ref_r->pc, cpu.pc, ANSI_NONE);
    } else {
      printf("%sref=0x%08x dut=0x%08x%s\n", 
             ANSI_FG_GREEN, ref_r->pc, cpu.pc, ANSI_NONE);
    }
    
    // Print GPRs
    printf("\nGeneral Purpose Registers:\n");
    for(i = 0; i < REGNUM; i++) {
      if(reg_mismatch[i]) {
        printf("%s%3s: ref=0x%08x dut=0x%08x%s  ", 
               ANSI_BG_RED, reg_name(i), ref_r->gpr[i], cpu.gpr[i], ANSI_NONE);
      } else {
        printf("%s%3s: ref=0x%08x dut=0x%08x%s  ", 
               ANSI_FG_GREEN, reg_name(i), ref_r->gpr[i], cpu.gpr[i], ANSI_NONE);
      }
      
      if((i + 1) % 3 == 0) printf("\n");
    }
    printf("\n=======================================================\n\n");
  }
  
  return flag;
}

void isa_difftest_attach() {
}