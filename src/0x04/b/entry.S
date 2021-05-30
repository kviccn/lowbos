/* Align all boot modules on i386 page (4KB) boundaries. */
#define MULTIBOOT_PAGE_ALIGN        0x00000001

/* Must pass memory information to OS. */
#define MULTIBOOT_MEMORY_INFO       0x00000002

#define MULTIBOOT_HEADER_MAGIC      0x1BADB002
#define MULTIBOOT_HEADER_FLAGS      MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
#define MULTIBOOT_HEADER_CHECKSUM   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

#define STACK_SIZE                  0x4000  // 16KB

.section .text
.globl _start
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long MULTIBOOT_HEADER_CHECKSUM

_start:
// 初始化栈指针
movl $(stack + STACK_SIZE), %esp

pushl %eax
pushl %ebx
call kernel_main
addl $8, %esp

pushl $halt_message
call cprintf
addl $4, %esp

hlt

.section .data
halt_message:
  .asciz  "Halted."

.section .bss
.comm stack, STACK_SIZE
