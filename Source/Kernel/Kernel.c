/*
 * Kernel.c
 */
#include <Kernel/Interrupts.h>
#include <Kernel/System.h>

void kb_func_test(void)
{
	unsigned char Keycode = inb(0x60);
	((char*)0xB8000)[2] = 'K';
}

void KMain()
{

	char *VIDEO_MEMORY = (char*)0xB8000;
	IDT_Setup();
	IDT_SetHandler(1, kb_func_test);
	SYS_STI();

	int n = 160;
	VIDEO_MEMORY[n++] = 'R';
	n++;
	VIDEO_MEMORY[n++] = 'F';
}
