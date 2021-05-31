#include "types.h"

// console.c
void cprintf(const char *fmt, ...);

// picirq.c
void picinit(void);
void eoi(uint8_t);

// trap.c
void tvinit(void);
void idtinit(void);

// vm.c
void seginit(void);
