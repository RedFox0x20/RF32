/*
 * Kernel.c
 */
#include <Kernel/Interrupts.h>
#include <Kernel/Video.h>
#include <Kernel/System.h>

void kb_func_test(void)
{
	unsigned char Keycode = inb(0x60);
	((char*)0xB8000)[2] = 'K';
}

void KMain(
		VIDEO_BIOSMode_t BIOSVideoData,
		void* MMAP)
{
	char *VIDEO_MEMORY = (char*)0xB8000;
	VIDEO_ModeInfo_t VideoModeData = VIDEO_GetModeInfo(BIOSVideoData);

	IDT_Setup();
	IDT_SetHandler(1, kb_func_test);
	SYS_STI();


	int n = 162;
	VIDEO_MEMORY[n++] = 'R';
	n++;
	VIDEO_MEMORY[n++] = 'F';
}
