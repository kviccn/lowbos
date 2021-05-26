/* Align all boot modules on i386 page (4KB) boundaries. */
#define MULTIBOOT_PAGE_ALIGN        0x00000001

/* Must pass memory information to OS. */
#define MULTIBOOT_MEMORY_INFO       0x00000002

#define MULTIBOOT_HEADER_MAGIC      0x1BADB002
#define MULTIBOOT_HEADER_FLAGS      MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
#define MULTIBOOT_HEADER_CHECKSUM   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

.section .text
.globl entry
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long MULTIBOOT_HEADER_CHECKSUM

entry:
lgdt gdtdesc

ljmp $0x8, $1f

1:
movw $0x10, %ax
movw %ax, %ds
movw %ax, %es
movw %ax, %fs
movw %ax, %gs
movw %ax, %ss

movw $'P' | 0x0a00, 0xb8000

hlt

.section .data
gdt:
  .quad 0
  .quad 0x00c09a00000007ff
  .quad 0x00c09200000007ff

gdtdesc:
  .word gdtdesc - gdt - 1
  .long gdt
