#include "defs.h"

void kernel_main(void)
{
  printint(9527, 10, 0);
  printint(-9527, 10, 1);
  printint(255, 16, 0);

  while (1)
    ;
}
