#define PTE_P 0x1
#define PTE_W 0x2

typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef uint32_t pde_t;
typedef uint32_t pte_t;

uint16_t *video_buffer = (uint16_t *)0xb8000;

__attribute__((__aligned__(4096)))
pde_t pgdir[1024];

__attribute__((__aligned__(4096)))
pte_t pt[1024];

void kernel_main(void)
{
  video_buffer[0] = 'A' | 0x0a00;
  pgdir[0] = (uint32_t)pt | PTE_P | PTE_W;

  for (int i = 0; i < 1024; i++)
  {
    pt[i] = (i << 12) | PTE_P | PTE_W;
  }

  asm volatile("movl %0, %%cr3" ::"r"(pgdir));

  uint32_t cr0;
  asm volatile("movl %%cr0, %0"
               : "=r"(cr0));
  cr0 |= 0x80000000;
  asm volatile("movl %0, %%cr0" ::"r"(cr0));

  video_buffer[1] = 'B' | 0x0a00;
}
