/*
 * Kernel.c
 */
#include <Kernel/Interrupts.h>
#include <Kernel/Video.h>
#include <Kernel/Keyboard.h>
#include <Kernel/System.h>

void KMain(
		VIDEO_BIOSMode_t BIOSVideoData,
		void* MMAP)
{
	VIDEO_ModeInfo_t VideoModeData = VIDEO_GetModeInfo(BIOSVideoData);
	VIDEO_UseModeInfo(VideoModeData);
	VIDEO_ClearScreen(0x00);	

	IDT_Setup();
	KEYBOARD_Init();

	SYS_STI();

	for (;;)
	{
		SYS_HLT();
	}

}
