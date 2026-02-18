#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <cpu/inst_ring.h>
#include <memory/paddr.h>
#include <stdbool.h> // 引入 bool 类型支持
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>

#define INST_BUFF 12

// 将内部数据结构和变量加上 static，防止被外部文件意外修改
static struct ringbuff {
  vaddr_t pc;
  word_t inst;
} ringbuff[INST_BUFF];

static int head = 0;
static int tail = 0;
static bool is_full = false; // 用于明确区分缓冲区是“满”还是“空”

void inst_ring_push(vaddr_t pc, word_t inst) {
  ringbuff[tail].pc = pc;
  ringbuff[tail].inst = inst;

  tail = (tail + 1) % INST_BUFF;

  if (is_full) {
    head = tail;
  } else if (tail == head) {
    is_full = true;
    head = tail;
  }
}

void inst_ring_pop() {
  if (!is_full && head == tail) {
    return; // 已经是空的，直接返回，防止越界
  }
  head = (head + 1) % INST_BUFF;
  is_full = false; // 只要弹出一个，状态就绝对不是满的
}

void inst_ring_display() {
  if (!is_full && head == tail) {
    printf("IRingBuf is empty.\n");
    return;
  }

  printf("--- Instruction Ring Buffer (IRingBuf) ---\n");
  int i = head;

  do {
    int next_i = (i + 1) % INST_BUFF;

    if (next_i == tail) {
      printf(" --> PC: 0x%08x, INST: 0x%08x\n", ringbuff[i].pc,
             ringbuff[i].inst);
    } else {
      printf("     PC: 0x%08x, INST: 0x%08x\n", ringbuff[i].pc,
             ringbuff[i].inst);
    }

    i = next_i;
  } while (i != tail);

  printf("------------------------------------------\n");
}