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
}
