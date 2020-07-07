#include "defs.h"

void kernel_main(void)
{
  seginit();
  cprintf("LowbOS @%d\n", 2020);

  while (1)
    ;
}
