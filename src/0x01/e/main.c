#include "defs.h"

void kernel_main(void)
{
  cprintf("LowbOS @%d\n", 2020);
  cprintf("%s\n", 0);
  cprintf("Hello, %s\n", "world!");

  while (1)
    ;
}
