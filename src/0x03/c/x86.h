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

struct gatedesc;

static inline void
lidt(struct gatedesc *p, int size)
{
  volatile uint16_t pd[3];

  pd[0] = size - 1;
  pd[1] = (uint32_t)p;
  pd[2] = (uint32_t)p >> 16;

  asm volatile("lidt (%0)" ::"r"(pd));
}

static inline void
cli(void)
{
  asm volatile("cli");
}

static inline void
sti(void)
{
  asm volatile("sti");
}

struct trapframe
{
  // 由 pusha 压栈的寄存器 (trapasm.S)
  uint32_t edi;
  uint32_t esi;
  uint32_t ebp;
  uint32_t oesp; // useless & ignored
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;

  // 由 push 压栈的寄存器 (trapasm.S)
  uint16_t gs;
  uint16_t padding1;
  uint16_t fs;
  uint16_t padding2;
  uint16_t es;
  uint16_t padding3;
  uint16_t ds;
  uint16_t padding4;
  uint32_t trapno;

  // x86 硬件压入的寄存器
  uint32_t err;
  uint32_t eip;
  uint16_t cs;
  uint16_t padding5;
  uint32_t eflags;

  // 跨特权级时会压栈的寄存器
  uint32_t esp;
  uint16_t ss;
  uint16_t padding6;
};

#endif
