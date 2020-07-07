#include "types.h"
#include "x86.h"

#define CRTPORT 0x3d4
static uint16_t *crt = (uint16_t *)0xb8000;

void cgaputc(int c)
{
  int pos;

  outb(CRTPORT, 14);
  pos = inb(CRTPORT + 1) << 8;
  outb(CRTPORT, 15);
  pos |= inb(CRTPORT + 1);

  if (c == '\n')
    pos += 80 - pos % 80;
  else if (c == '\b')
  {
    if (pos > 0)
      --pos;
  }
  else
    crt[pos++] = (c & 0xff) | 0x0700;

  outb(CRTPORT, 14);
  outb(CRTPORT + 1, pos >> 8);
  outb(CRTPORT, 15);
  outb(CRTPORT + 1, pos);
  crt[pos] = ' ' | 0x0700;
}
