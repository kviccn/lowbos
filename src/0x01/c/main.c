#include "defs.h"

char *message = "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!"
                "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!";

void kernel_main(void)
{

  for (int i = 0; message[i] != '\0'; i++)
  {
    cgaputc(message[i]);
  }

  while (1)
    ;
}
