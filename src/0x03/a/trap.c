#include "types.h"
#include "defs.h"
#include "mmu.h"
#include "x86.h"

// 中断描述符表
struct gatedesc idt[256];
extern uint32_t vectors[]; // 中断处理程序入口地址构成的数组 (在 vectors.S 中)

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
  cprintf("trapno: %d, eip: %x, err: %d\n", tf->trapno, tf->eip, tf->err);
}
