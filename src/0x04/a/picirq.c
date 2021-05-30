#include "x86.h"
#include "traps.h"

// 两块 8259A 可编程中断控制器的 I/O 端口地址
#define IO_PIC1 0x20 // Master (IRQs 0-7)
#define IO_PIC2 0xA0 // Slave (IRQs 8-15)

#define IRQ_SLAVE 2 // Slave 连接到 Master 上的引脚

static bool didinit;

void picinit(void)
{
  didinit = true;

  // 屏蔽所有中断
  outb(IO_PIC1 + 1, 0xFF);
  outb(IO_PIC2 + 1, 0xFF);

  // 初始化 master (8259A-1)

  // ICW1:
  outb(IO_PIC1, 0x11);

  // ICW2: 中断向量号
  outb(IO_PIC1 + 1, T_IRQ0);

  // ICW3:
  outb(IO_PIC1 + 1, 1 << IRQ_SLAVE);

  // ICW4:
  outb(IO_PIC1 + 1, 0x1);

  // 初始化 slave (8259A-2)
  outb(IO_PIC2, 0x11);           // ICW1
  outb(IO_PIC2 + 1, T_IRQ0 + 8); // ICW2
  outb(IO_PIC2 + 1, IRQ_SLAVE);  // ICW3
  outb(IO_PIC2 + 1, 0x1);        // ICW4

  // 放开所有中断
  outb(IO_PIC1 + 1, 0x00);
  outb(IO_PIC2 + 1, 0x00);
}

void eoi(uint8_t intno)
{
  if (intno >= T_IRQ0 + 8)
  {
    outb(IO_PIC2, 0x20);
  }
  outb(IO_PIC1, 0x20);
}
