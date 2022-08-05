#ifndef KERNEL_SYSTEM_H
#define KERNEL_SYSTEM_H

#define NULL (void*)0
#define SYS_CLI() __asm__ volatile ("cli")
#define SYS_STI() __asm__ volatile ("sti")

void outb(
		unsigned short port,
		unsigned char val);

void outw(
		unsigned short port,
		unsigned short val);

unsigned char inb(unsigned short port);

typedef struct
{
	unsigned int 
		EDI,
		ESI,
		EBP,
		ESP,
		EBX,
		EDX,
		ECX,
		EAX;
} Registers32_t;

#endif /* KERNEL_SYSTEM_H */
