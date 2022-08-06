#include <Kernel/Video.h>

#define VIDEO_INVALID_MODE \
	(VIDEO_ModeInfo_t){ \
		.Type   = VIDEO_MODE_TYPE_INVALID, \
		.Mode   = 0, \
		.Cols   = 0, \
		.Rows   = 0, \
		.Depth  = 0, \
		.Memory = (void*)0 \
	}

VIDEO_ModeInfo_t VIDEO_ModesList[] =
{
	/* EGA MODES */
	/* Mode 0 40x25, 16/8 shades */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_TEXT,
		.Mode = 0,
		.Cols = 25,
		.Rows = 40,
		.Depth = 4,
		.Memory = (void*)0xB8000
	},
	/* Mode 1 40x25, 16/8 colours */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_TEXT,
		.Mode = 1,
		.Cols = 25,
		.Rows = 40,
		.Depth = 4,
		.Memory = (void*)0xB8000
	},
	/* Mode 2 80x25, 16/8 shades */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_TEXT,
		.Mode = 2,
		.Cols = 25,
		.Rows = 80,
		.Depth = 4,
		.Memory = (void*)0xB8000
	},
	/* Mode 3 80x25, 16/8 colours */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_TEXT,
		.Mode = 3,
		.Cols = 25,
		.Rows = 80,
		.Depth = 4,
		.Memory = (void*)0xB8000
	},
	/* Mode 4, 320x200 graphic, 4 colours */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 4,
		.Rows = 200,
		.Cols = 320,
		.Depth = 2,
		.Memory = (void*)0xB8000
	},
	/* Mode 5, 320x200 graphic, 4 shades */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 5,
		.Rows = 200,
		.Cols = 320,
		.Depth = 2,
		.Memory = (void*)0xB8000
	},
	/* Mode 6, 640x200 BW */
	(VIDEO_ModeInfo_t)
	{
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 6,
		.Rows = 200,
		.Cols = 640,
		.Depth = 1,
		.Memory = (void*)0xB8000
	},
	/* Mode 80x25 9x14 chars TTL Mono */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_TEXT,
		.Mode = 7,
		.Rows = 25,
		.Cols = 45,
		.Depth = 2,
		.Memory = (void*)0xB0000
	},
	/* Modes 8,9,a,b,c are PCjr or Reserved */
	VIDEO_INVALID_MODE,
	VIDEO_INVALID_MODE,
	VIDEO_INVALID_MODE,
	VIDEO_INVALID_MODE,
	VIDEO_INVALID_MODE,
	/* VGA MODES */
	/* Mode 0x0D 320x200 16 colours */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 0x0D,
		.Rows = 200,
		.Cols = 320,
		.Depth = 4,
		.Memory = (void*)0xA0000,
	},
	/* Mode 0x0E 640x200 16 colours */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 0x0E,
		.Rows = 200,
		.Cols = 640,
		.Depth = 4,
		.Memory = (void*)0xA0000
	},
	/* Mode 0x0F 640x350 3 BW */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 0x0F,
		.Rows = 350,
		.Cols = 640,
		.Depth = 2,
		.Memory = (void*)0xA0000
	},
	/* Mode 0x10 640x350 4 or 16 colours */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 0x10,
		.Rows = 350,
		.Cols = 640,
		.Depth = 4,
		.Memory = (void*)0xA0000
	},
	/* Mode 0x11 640x480 BW */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 0x11,
		.Rows = 480,
		.Cols = 640,
		.Depth = 1,
		.Memory = (void*)0xA0000
	},
	/* Mode 0x12 640x480 16 colours */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 0x12,
		.Rows = 480,
		.Cols = 640,
		.Depth = 4,
		.Memory = (void*)0xA0000
	},
	/* Mode 0x13 640x480 256 colours */
	(VIDEO_ModeInfo_t){
		.Type = VIDEO_MODE_TYPE_GRAPHICS,
		.Mode = 0x13,
		.Rows = 480,
		.Cols = 640,
		.Depth = 8,
		.Memory = (void*)0xA0000
	}
	/* 0x14 through 0x7F modes are OEM dependant */
};

#undef VIDEO_INVALID_MODE
