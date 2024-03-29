#include "types.h"
#include "defs.h"
#include "mmu.h"
#include "x86.h"
#include "traps.h"

// 中断描述符表
struct gatedesc idt[256];
extern uint32_t vectors[]; // 中断处理程序入口地址构成的数组 (在 vectors.S 中)
uint32_t ticks;

void tvinit(void)
{
  for (int i = 0; i < 256; i++)
    SETGATE(idt[i], 0, SEG_KCODE << 3, vectors[i], 0);
}

void idtinit(void)
{
  lidt(idt, sizeof(idt));
}

void trap(struct trapframe *tf)
{
  // cprintf("trapno: %d, eip: %x, err: %d\n", tf->trapno, tf->eip, tf->err);

  switch (tf->trapno)
  {
  // case T_IRQ0 ... T_IRQ0 + 16:
  //   eoi(tf->trapno);
  //   break;
  case T_IRQ0 + IRQ_TIMER:
    cprintf("tick: %d\n", ticks++);
    eoi(tf->trapno);
    break;
  }
}
