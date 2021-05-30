#include "defs.h"
#include "x86.h"

void kernel_main(void)
{
  seginit();
  tvinit();
  idtinit();
  picinit();

  cprintf("LowbOS @%d\n", 2020);

  asm volatile("int $0x3");
  asm volatile("int $0x4");

  // int i = 1 / 0;

  // sti();
}
