[BITS 32]
[SECTION .text]
[EXTERN KMain]

KEntry:
	call KMain	

KHalt:
	hlt
	jmp KHalt
