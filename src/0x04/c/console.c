#include "x86.h"

#define COLUMNS 80
#define ROWS 25
#define VIDEO 0xB8000

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
static uint16_t *crt = (uint16_t *)VIDEO;

static void cgaputc(int c)
{
  int pos;

  outb(CRTPORT, 14);
  pos = inb(CRTPORT + 1) << 8;
  outb(CRTPORT, 15);
  pos |= inb(CRTPORT + 1);

  if (c == '\n')
    pos += COLUMNS - pos % COLUMNS;
  else if (c == '\b')
  {
    if (pos > 0)
      --pos;
  }
  else
    crt[pos++] = (c & 0xff) | 0x0f00;

  if (pos >= COLUMNS * ROWS)
  {
    for (int i = 0; i < COLUMNS * (ROWS - 1); i++)
      crt[i] = crt[i + COLUMNS];
    for (int i = COLUMNS * (ROWS - 1); i < COLUMNS * ROWS; i++)
      crt[i] = 0x0f00 | ' ';
    pos -= COLUMNS;
  }

  outb(CRTPORT, 14);
  outb(CRTPORT + 1, pos >> 8);
  outb(CRTPORT, 15);
  outb(CRTPORT + 1, pos);
  crt[pos] = ' ' | 0x0f00;
}

void consputc(int c)
{
  cgaputc(c);
}
