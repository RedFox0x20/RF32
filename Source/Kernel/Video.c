/*
 * Kernel/Video.c
 */

#include <Kernel/Video.h>
#include <Kernel/System.h>

extern VIDEO_ModeInfo_t VIDEO_ModesList[];

static VIDEO_ModeInfo_t* VIDEO_ModeInfo = NULL;

void VIDEO_UseModeInfo()
{
	
}

VIDEO_ModeInfo_t VIDEO_GetModeInfo(VIDEO_BIOSMode_t BIOSModeData)
{
	if (BIOSModeData.Mode <= 0x13)
	{
		return VIDEO_ModesList[BIOSModeData.Mode];
	}
	else
	{
		return (VIDEO_ModeInfo_t){ VIDEO_MODE_TYPE_INVALID,0,0,0,0,NULL};
	}
}

