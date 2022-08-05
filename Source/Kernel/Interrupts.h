#ifndef KERNEL_INTERRUPTS_H
#define KERNEL_INTERRUPTS_H

void IDT_Setup(void);
void IDT_SetHandler(unsigned int ID, void (*func)(void));

#endif
