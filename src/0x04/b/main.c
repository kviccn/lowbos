#include "defs.h"
#include "x86.h"
#include "multiboot.h"

void kernel_main(multiboot_info_t *mbi, uint32_t magic)
{
  seginit();
  tvinit();
  idtinit();
  picinit();

  cprintf("LowbOS @%d\n", 2021);

  asm volatile("int $0x3");
  asm volatile("int $0x4");

  // int i = 1 / 0;

  sti();

  for (;;)
    ;
}
