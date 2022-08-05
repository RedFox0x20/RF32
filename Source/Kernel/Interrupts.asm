[BITS 32]
[SECTION .text]

[EXTERN IDT_InterruptHandler]

%macro IDT_Interrupt 1

[GLOBAL IDT_Interrupt%1]
IDT_Interrupt%1:
	pushad
	push word %1
	call IDT_InterruptHandler
	pop word ax
	popad
	iretd

%endmacro

IDT_Interrupt 0
IDT_Interrupt 1
IDT_Interrupt 2
IDT_Interrupt 3
IDT_Interrupt 4
IDT_Interrupt 5
IDT_Interrupt 6
IDT_Interrupt 7
IDT_Interrupt 8
IDT_Interrupt 9
IDT_Interrupt 10
IDT_Interrupt 11
IDT_Interrupt 12
IDT_Interrupt 13
IDT_Interrupt 14
IDT_Interrupt 15

[GLOBAL IDT_SyscallHandlerStub]
IDT_SyscallHandlerStub:
	pushad
	push word 0x0080
	call IDT_InterruptHandler
	pop word ax
	popad
	iretd

[GLOBAL IDT_SetIDT]
IDT_SetIDT:
	cli
	mov edx, [esp+4]
	lidt [edx]
	ret
