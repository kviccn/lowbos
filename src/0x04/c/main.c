#include "defs.h"
#include "x86.h"
#include "multiboot.h"

void kernel_main(multiboot_info_t *mbi, uint32_t magic)
{
  seginit();
  tvinit();
  idtinit();
  picinit();

  cprintf("LowbOS @%d\n", 2021);

  asm volatile("int $0x3");
  asm volatile("int $0x4");

  // int i = 1 / 0;

  // sti();

  cprintf("mem_lower = %dKB, mem_upper = %dKB\n", mbi->mem_lower, mbi->mem_upper);

  multiboot_memory_map_t *mmap;
  cprintf("mmap_addr = 0x%x, mmap_length = 0x%x\n", mbi->mmap_addr, mbi->mmap_length);
  for (mmap = (multiboot_memory_map_t *)mbi->mmap_addr;
       (unsigned long)mmap < mbi->mmap_addr + mbi->mmap_length;
       mmap = (multiboot_memory_map_t *)((unsigned long)mmap + mmap->size + sizeof(mmap->size)))
  {
    cprintf(" base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n",
            (unsigned)(mmap->addr >> 32), (unsigned)(mmap->addr & 0xffffffff),
            (unsigned)(mmap->len >> 32), (unsigned)(mmap->len & 0xffffffff),
            (unsigned)mmap->type);
  }
}
