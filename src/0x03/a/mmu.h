#include "types.h"

// 段选择子
#define SEG_KCODE 1 // 内核代码段
#define SEG_KDATA 2 // 内核数据+堆栈段
#define SEG_UCODE 3 // 用户代码段
#define SEG_UDATA 4 // 用户数据+堆栈段
#define SEG_TSS 5   // 任务状态段

#define NSEGS 6 // 段数量

// 段描述符
struct segdesc
{
  uint32_t lim_15_0 : 16;
  uint32_t base_15_0 : 16;
  uint32_t base_23_16 : 8;
  uint32_t type : 4;
  uint32_t s : 1;
  uint32_t dpl : 2;
  uint32_t p : 1;
  uint32_t lim_19_16 : 4;
  uint32_t avl : 1;
  uint32_t rsv1 : 1;
  uint32_t db : 1;
  uint32_t g : 1;
  uint32_t base_31_24 : 8;
};

#define SEG(type, base, lim, dpl)                                 \
  (struct segdesc)                                                \
  {                                                               \
    ((lim) >> 12) & 0xffff, (uint32_t)(base)&0xffff,              \
        ((uint32_t)(base) >> 16) & 0xff, type, 1, dpl, 1,         \
        (uint32_t)(lim) >> 28, 0, 0, 1, 1, (uint32_t)(base) >> 24 \
  }

#define DPL_USER 0x3 // 用户 DPL

// 应用段 type 位
#define STA_X 0x8 // 可执行段
#define STA_W 0x2 // 可写段(不可执行)
#define STA_R 0x2 // 可读段(可执行)

// 系统段 type 位
#define STS_T32A 0x9 // 可用 32位 TSS
#define STS_IG32 0xE // 32位 中断门
#define STS_TG32 0xF // 32位 陷阱门

// 中断/陷阱门描述符
struct gatedesc
{
  uint32_t off_15_0 : 16;
  uint32_t cs : 16;
  uint32_t args : 5;
  uint32_t rsv1 : 3;
  uint32_t type : 4;
  uint32_t s : 1;
  uint32_t dpl : 2;
  uint32_t p : 1;
  uint32_t off_31_16 : 16;
};

#define SETGATE(gate, istrap, sel, off, d)        \
  {                                               \
    (gate).off_15_0 = (uint32_t)(off)&0xffff;     \
    (gate).cs = (sel);                            \
    (gate).args = 0;                              \
    (gate).rsv1 = 0;                              \
    (gate).type = (istrap) ? STS_TG32 : STS_IG32; \
    (gate).s = 0;                                 \
    (gate).dpl = (d);                             \
    (gate).p = 1;                                 \
    (gate).off_31_16 = (uint32_t)(off) >> 16;     \
  }
