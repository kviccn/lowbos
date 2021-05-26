#include "x86.h"

static void consputc(int);

static void printint(int xx, int base, int sign)
{
  static char digits[] = "0123456789abcdef";
  char buf[16];
  int i;
  unsigned int x;

  if (sign && (sign = xx < 0))
    x = -xx;
  else
    x = xx;

  i = 0;
  do
  {
    buf[i++] = digits[x % base];
  } while ((x /= base) != 0);

  if (sign)
    buf[i++] = '-';

  while (--i >= 0)
    consputc(buf[i]);
}

void cprintf(const char *fmt, ...)
{
  uint32_t *argp;
  char *s;
  int c;

  argp = (uint32_t *)(&fmt + 1);

  for (int i = 0; (c = fmt[i] & 0xff) != 0; i++)
  {
    if (c != '%')
    {
      consputc(c);
      continue;
    }

    c = fmt[++i] & 0xff;

    if (c == 0)
      break;

    switch (c)
    {
    case 'd':
      printint(*argp++, 10, 1);
      break;
    case 'x':
    case 'p':
      printint(*argp++, 16, 0);
      break;
    case 's':
      if ((s = (char *)*argp++) == 0)
        s = "(null)";
      for (; *s; s++)
        consputc(*s);
      break;
    case '%':
      consputc('%');
      break;
    default:
      consputc('%');
      consputc(c);
      break;
    }
  }
}

#define CRTPORT 0x3d4
static uint16_t *crt = (uint16_t *)0xb8000;

static void cgaputc(int c)
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

  if (pos >= 80 * 25)
  {
    for (int i = 0; i < 80 * 24; i++)
      crt[i] = crt[i + 80];
    for (int i = 80 * 24; i < 80 * 25; i++)
      crt[i] = 0x0700 | ' ';
    pos -= 80;
  }

  outb(CRTPORT, 14);
  outb(CRTPORT + 1, pos >> 8);
  outb(CRTPORT, 15);
  outb(CRTPORT + 1, pos);
  crt[pos] = ' ' | 0x0700;
}

void consputc(int c)
{
  cgaputc(c);
}
