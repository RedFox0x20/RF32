#ifndef KERNEL_KEYBOARD_H
#define KERNEL_KEYBOARD_H

enum KEYBOARD_KEY_STATE
{
	KEYBOARD_KEY_STATE_UP = 0,
	KEYBOARD_KEY_STATE_DOWN
};

void KEYBOARD_Init();

#endif