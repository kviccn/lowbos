#ifndef __X86_H_
#define __X86_H_

#include "types.h"

static inline uint8_t
inb(uint16_t port)
{
  uint8_t data;
  asm volatile("inb %1,%0"
               : "=a"(data)
               : "d"(port));
  return data;
}

static inline void
outb(uint16_t port, uint8_t data)
{
  asm volatile("outb %0,%1"
               :
               : "a"(data), "d"(port));
}

static inline void
insl(int port, void *addr, int cnt)
{
  asm volatile("cld; rep insl"
               : "=D"(addr), "=c"(cnt)
               : "d"(port), "0"(addr), "1"(cnt)
               : "memory", "cc");
}

struct segdesc;

static inline void
lgdt(struct segdesc *p, int size)
{
  volatile uint16_t pd[3];

  pd[0] = size - 1;
  pd[1] = (uint32_t)p;
  pd[2] = (uint32_t)p >> 16;

  asm volatile("lgdt (%0)" ::"r"(pd));
}

#endif
