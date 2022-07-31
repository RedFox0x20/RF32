;------------------------------------------------------------------------------;
; Bootloader Stage 2
;------------------------------------------------------------------------------;
[BITS 16]                              ;At this stage we are still in real mode
[ORG 0x8000]                           ;Stage 2 will be loaded to this address
                                       ; so the offset is required

Stage2_Entry:                          ;Stage 2 entry point
	mov ah, 0x0E                       ;0x10 print command
	mov al, '2'                        ;'2' as an identifier
	xor bx, bx                         ;Screen 0
	int 0x10                           ;Call BIOS int 0x10

	jmp Stage2_Halt                    ;Stop for now


Stage2_Halt:                           ;Stage 2 halt routine
	cli                                ;Disable interrupts
	hlt                                ;Halt the CPU
	jmp Stage2_Halt                    ;Just in case the CPU is woken up

