#ifndef KERNEL_INTERRUPTS_H
#define KERNEL_INTERRUPTS_H

#define IDT_HANDLER_PIT 0
#define IDT_HANDLER_KEYBOARD 1
/* Here for completeness, this is never raised. */
#define IDT_HANDLER_CASCADE 2
#define IDT_HANDLER_COM2 3
#define IDT_HANDLER_COM1 4
#define IDT_HANDLER_LPT2 5
#define IDT_HANDLER_FLOPPY 6
/* LPT1 is considered to be potentially spurious and unreliable */
#define IDT_HANDLER_LPT1 7
#define IDT_HANDLER_CMOS 8
#define IDT_HANDLER_PS2_MOUSE 12
#define IDT_HANDLER_FPU 13
#define IDT_HANDLER_COPROCESSOR 13
#define IDT_HANDLER_INTER_PROCESSOR 13
#define IDT_HANDLER_ATA_PRIMARY 14
#define IDT_HANDLER_ATA_SECONDARY 15
#define IDT_HANDLER_SYSCALLS 0x80

void IDT_Setup(void);
void IDT_SetHandler(unsigned int ID, void (*func)(void));

#endif
