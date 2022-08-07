#ifndef KERNEL_VIDEO_H
#define KERNEL_VIDEO_H

typedef struct
{
	unsigned short Mode;
	unsigned short Cols;
} VIDEO_BIOSMode_t;

typedef enum
{
	VIDEO_MODE_TYPE_INVALID,
	VIDEO_MODE_TYPE_TEXT,
	VIDEO_MODE_TYPE_GRAPHICS
} VIDEO_MODE_TYPE_t;

typedef struct
{
	VIDEO_MODE_TYPE_t Type;
	unsigned short Mode;
	unsigned short Cols;
	unsigned short Rows;
	unsigned short Depth;
	void* Memory;
	unsigned int MemorySize;
} VIDEO_ModeInfo_t;

VIDEO_ModeInfo_t VIDEO_GetModeInfo(VIDEO_BIOSMode_t BIOSModeData);

void VIDEO_UseModeInfo(VIDEO_ModeInfo_t ModeInfo);
void VIDEO_PutCharTextXY(
		char c,
		char Attributes,
		unsigned int X,
		unsigned int Y);
void VIDEO_putch(char c, char Attributes);
void VIDEO_puts(char* s, char Attributes);
void VIDEO_Scroll(unsigned int n);

#endif /* KERNEL_VIDEO_H */
