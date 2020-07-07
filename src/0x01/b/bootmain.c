#include "elf.h"
#include "x86.h"

#define SECTSIZE 512

void readseg(uint8_t *pa, uint32_t count, uint32_t offset);

void bootmain(void)
{
  struct elfhdr *elf;
  struct proghdr *ph, *eph;
  void (*entry)(void);
  uint8_t *pa;

  elf = (struct elfhdr *)0x10000;

  readseg((uint8_t *)elf, 4096, 0);

  if (elf->magic != ELF_MAGIC)
    return;

  ph = (struct proghdr *)((uint8_t *)elf + elf->phoff);
  eph = ph + elf->phnum;
  for (; ph < eph; ph++)
  {
    pa = (uint8_t *)ph->paddr;
    readseg(pa, ph->filesz, ph->off);
    for (int i = 0; i < ph->memsz - ph->filesz; i++)
    {
      *((char *)ph->paddr + ph->filesz + i) = 0;
    }
  }

  entry = (void (*)(void))(elf->entry);
  entry();
}

void waitdisk(void)
{
  while ((inb(0x1F7) & 0xC0) != 0x40)
    ;
}

void readsect(void *dst, uint32_t offset)
{
  waitdisk();
  outb(0x1F2, 1);
  outb(0x1F3, offset);
  outb(0x1F4, offset >> 8);
  outb(0x1F5, offset >> 16);
  outb(0x1F6, (offset >> 24) | 0xE0);
  outb(0x1F7, 0x20);

  waitdisk();
  insl(0x1F0, dst, SECTSIZE / 4);
}

void readseg(uint8_t *pa, uint32_t count, uint32_t offset)
{
  uint8_t *epa;
  epa = pa + count;

  pa -= offset % SECTSIZE;
  offset = (offset / SECTSIZE) + 1;

  for (; pa < epa; pa += SECTSIZE, offset++)
    readsect(pa, offset);
}
