#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

#define MCAUSE_ECALL_U 8
#define MCAUSE_ECALL_S 9
#define MCAUSE_ECALL_M 11

#if __riscv_xlen == 64
#define MCAUSE_IRQ_TIMER_M 0x8000000000000007ull
#define MCAUSE_IRQ_TIMER_S 0x8000000000000005ull
#else
#define MCAUSE_IRQ_TIMER_M 0x80000007ul
#define MCAUSE_IRQ_TIMER_S 0x80000005ul
#endif

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case MCAUSE_ECALL_U:
      case MCAUSE_ECALL_S:
      case MCAUSE_ECALL_M:
        if (c->GPR1 == -1) { 
          ev.event = EVENT_YIELD;
        } else {
          ev.event = EVENT_SYSCALL;
        }
        c->mepc += 4; // 同步异常，必须 +4 跳过 ecall 指令
        break;
      case MCAUSE_IRQ_TIMER_S:
      case MCAUSE_IRQ_TIMER_M:
        ev.event = EVENT_IRQ_TIMER;
        // 中断是异步的，返回时应该重新执行被中断的指令，不需要 +4
        break;
      default: 
        ev.event = EVENT_ERROR; 
        break;
    }
    c = user_handler(ev, c);
    assert(c != NULL);
  }
  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  Context *c = (Context *)((uintptr_t)kstack.end - sizeof(Context));
  
  memset(c, 0, sizeof(Context));
  
  c->mepc = (uintptr_t)entry;
  c->mstatus = 0x1800; // M-mode
  
  // RISC-V ABI 规定 a0 传参
  c->gpr[10] = (uintptr_t)arg; 
  // 设置 sp (x2) 寄存器
  c->gpr[2] = (uintptr_t)c; 
  
  return c;
}

void yield() {
#ifdef __riscv_e
  asm volatile("li a5, -1; ecall");
#else
  asm volatile("li a7, -1; ecall");
#endif
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
