/*
 * Kernel/Video.c
 */

#include <Kernel/Video.h>
#include <Kernel/System.h>

extern VIDEO_ModeInfo_t VIDEO_ModesList[];
static VIDEO_ModeInfo_t VIDEO_ModeInfo;
static struct {
	unsigned short CursorPosition;
} VIDEO_TextModeData;

void VIDEO_UseModeInfo(VIDEO_ModeInfo_t ModeInfo)
{
	VIDEO_ModeInfo = ModeInfo;
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

void VIDEO_putch(char c, char Attributes)
{
	if (VIDEO_TextModeData.CursorPosition > VIDEO_ModeInfo.Cols * 2 *
			VIDEO_ModeInfo.Rows)
	{
		VIDEO_Scroll(1);
	}

	if (c == '\n')
	{
		VIDEO_TextModeData.CursorPosition += VIDEO_ModeInfo.Cols*2;
		VIDEO_TextModeData.CursorPosition -= 
			VIDEO_TextModeData.CursorPosition %	(VIDEO_ModeInfo.Cols*2);
	}
	else
	{
		((char*)VIDEO_ModeInfo.Memory)[VIDEO_TextModeData.CursorPosition++] = c;
		((char*)VIDEO_ModeInfo.Memory)[VIDEO_TextModeData.CursorPosition++] =
			Attributes;
	}
}

void VIDEO_puts(char* str, char Attributes)
{
	char *str_ptr = str;
	while (*str_ptr != 0)
	{
		VIDEO_putch(*str_ptr++, Attributes);
	}
}

void VIDEO_Scroll(unsigned int n)
{
	for (
			int i = VIDEO_ModeInfo.Cols * 2 * n; 
			i < VIDEO_ModeInfo.Cols * 2 * VIDEO_ModeInfo.Rows; 
			i++)
	{
		((char*)VIDEO_ModeInfo.Memory)[i-VIDEO_ModeInfo.Cols*2*n] =
			((char*)VIDEO_ModeInfo.Memory)[i];
	}
	VIDEO_TextModeData.CursorPosition -= VIDEO_ModeInfo.Cols * 2 * n;
}

void VIDEO_ClearScreen(char Attributes)
{
	int WriteValue = ' ' << 16 | Attributes << 24 | ' ' |  Attributes << 8;
	for (int i = 0; i < VIDEO_ModeInfo.MemorySize / sizeof(int); i++)
	{
		((int*)VIDEO_ModeInfo.Memory)[i] = WriteValue;
	}
}
