#include <Kernel/Keyboard.h>
#include <Kernel/Interrupts.h>
#include <Kernel/System.h>
#include <Kernel/KeyboardLayouts/KeyboardLayout_GB.h>

#include <Kernel/Video.h>

#define KEYBOARD_DATA_PORT 0x60

void KEYBOARD_Handler()
{
	unsigned char Keycode = inb(KEYBOARD_DATA_PORT);
	unsigned char Extended = (Keycode == 0xE0) ? 1 : 0;
	if (Extended)
	{
		Keycode = inb(KEYBOARD_DATA_PORT);	
	}
	unsigned char State = Keycode & 0x80 ? 
		KEYBOARD_KEY_STATE_UP 
		: KEYBOARD_KEY_STATE_DOWN;
	
	if (State == KEYBOARD_KEY_STATE_DOWN)
	{
		VIDEO_putch(Keyboard_Layout[Keycode ^ 0x80],4);
	}
}

void KEYBOARD_Init()
{
	IDT_SetHandler(IDT_HANDLER_KEYBOARD, KEYBOARD_Handler);
}
