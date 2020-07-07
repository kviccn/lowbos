.p2align 2
.text
.globl multiboot_header
multiboot_header:
  #define magic 0x1badb002
  #define flags 0
  .long magic
  .long flags
  .long (-(magic + flags))

.globl _start
_start:

  movl $kernel_main, %eax
  jmp *%eax
