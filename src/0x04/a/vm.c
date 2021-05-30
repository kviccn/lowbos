#include "types.h"
#include "defs.h"
#include "x86.h"
#include "mmu.h"

struct segdesc gdt[NSEGS];

void seginit(void)
{
  gdt[SEG_KCODE] = SEG(STA_X | STA_R, 0, 0xffffffff, 0);
  gdt[SEG_KDATA] = SEG(STA_W, 0, 0xffffffff, 0);
  gdt[SEG_UCODE] = SEG(STA_X | STA_R, 0, 0xffffffff, DPL_USER);
  gdt[SEG_UDATA] = SEG(STA_W, 0, 0xffffffff, DPL_USER);
  lgdt(gdt, sizeof(gdt));

  asm volatile("movw $0x10, %ax\n\t"
               "movw %ax, %ds\n\t"
               "movw %ax, %es\n\t"
               "movw %ax, %fs\n\t"
               "movw %ax, %gs\n\t"
               "movw %ax, %ss\n\t"
               "ljmp $0x8, $1f\n\t"
               "1:");
}
