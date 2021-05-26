.globl alltraps
alltraps:
  # 构建 trap frame
  pushl %ds
  pushl %es
  pushl %fs
  pushl %gs
  pushal
  
  # 设置数据段
  movw $(2 << 3), %ax
  movw %ax, %ds
  movw %ax, %es

  # 以 trap frame 为参数调用 trap, 此时 %esp 指向 trap frame
  pushl %esp
  call trap
  addl $4, %esp

.globl trapret
trapret:
  popal
  popl %gs
  popl %fs
  popl %es
  popl %ds
  addl $0x8, %esp  # 弹出 trapno 和 errcode
  iret
