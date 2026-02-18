#ifndef __INST_RING_H__
#define __INST_RING_H__

// 引入 vaddr_t 和 word_t 的类型定义
// 在 NEMU 系统中通常存在于 isa.h 或 common.h 中
#include <isa.h>

// 将一条指令及其对应的 PC 压入环形缓冲区
void inst_ring_push(vaddr_t pc, word_t inst);

// 弹出最早的一条指令 (通常在作为追踪工具时无需手动调用，满后会自动覆盖)
void inst_ring_pop(void);

// 打印当前环形缓冲区中的所有历史指令
void inst_ring_display(void);

#endif // __INST_RING_H__