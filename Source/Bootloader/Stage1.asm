;------------------------------------------------------------------------------;
; Bootloader Stage 1
;------------------------------------------------------------------------------;
[BITS 16]                              ;Tell NASM to use 16 bit mode
[ORG 0x7C00]                           ;Tell NASM our offset position

%define STAGE_2_LOAD_ADDR 0x8000       ;Stage 2 will be loaded to this address
%define STACK_TOP 0x8000               ;Define a stack starting from 0x8000
                                       ; this will provide a 30k stack for
									   ; protected mode

Boot:
	mov byte [BootDevice], dl          ;BIOS commonly sets dl to be the boot dev

	cli                                ;Disable interrupts
	xor ax, ax                         ;Clear AX
	mov ds, ax                         ;Clear DS
	mov es, ax                         ;Clear ES

Boot_Stack_Setup:
	mov ss, ax                         ;Set the stack segment
	mov sp, STACK_TOP                  ;Set the stack pointer
	mov bp, STACK_TOP                  ;Set the stack base
	sti                                ;Enable interrupts

Boot_Booting_Status:
	mov ah, 0x0E                       ;0x10 Print command
    mov al, 'B'                        ;Load the character 'B'
    xor bx, bx                         ;Clear BX for buffer
    int 0x10                           ;Call BIOS 0x10 interrupt

Boot_Reset_Drive:                      ;Boot disk reset routine
	xor ax, ax                         ;Command 0, clear AX
    mov dl, byte [BootDevice]          ;Set dl as boot device
	int 0x13                           ;Call BIOS 0x13 interrupt
	jc Boot_Reset_Drive                ;If error, try again

Boot_Load:                             ;Load stage 2 routine
	mov ah, 0x02                       ;0x13 Read command
	mov al, byte [LoadSize]            ;Load the number of sectors to read
	mov bx, STAGE_2_LOAD_ADDR          ;Set the load address
	mov cx, word [LoadCylinder]        ;Set the cylinder to access
	shl cx, 6                          ;Cylinder is the first 10 bits of cx
	or cl, byte [LoadSector]           ;Set Sector to start from
	mov dh, byte [LoadHead]            ;Set the disk head
	mov dl, byte [BootDevice]          ;Set the boot device
	int 0x13                           ;Call BIOS 0x13 interrupt

	jc Boot_Error                      ;If error, abort
	cmp al, [LoadSize]                 ;Check all the sectors loaded
	jne Boot_Error                     ;If not, abort

	movzx ax, byte [LoadCounter]       ;Load the LoadCounter
	mov bl, byte [LoadSize]            ;Load the number of sectors loaded
	sub al, bl                         ;LoadCounter - LoadSize
	jle Boot_Success                   ;If <= zero, load finished

	; Foundation for loading more than 17 sectors
	;mov word [LoadCounter], ax         ;Set the new counter value
	;mov byte [LoadSize], 18            ;Default back to 18 sectors
	;mov byte [LoadSector], 1           ;Default to reading from the first sector
	;mov ax, word [LoadCylinder]
	;inc ax
	;mov word [LoadCylinder], ax
	;mov bx, 2
	;div ax, bx
	;cmp dx, 0

	
	jmp Boot_Error                     ;TEMP : Just error
	;jmp Boot_Load                      ;Perform the next load iteration

Boot_Success:
	mov ah, 0x0E
	mov al, 'Y'
	xor bx, bx
	int 0x10
	jmp Boot_Halt


Boot_Error:
	mov ah, 0x0E
	mov al, 'E'
	xor bx, bx
	int 0x10

Boot_Halt:
	cli
	hlt
	jmp Boot_Reset_Drive

;------------------------------------------------------------------------------;
; DATA
;------------------------------------------------------------------------------;
BootDevice:  db 0xFF
LoadCounter: db 18
LoadSize:    db 17
LoadSector:  db 2
LoadCylinder:dw 0
LoadTrack:   db 0
LoadHead:    db 0

;------------------------------------------------------------------------------;
; Boot sig
;------------------------------------------------------------------------------;
times 510 - ($-$$) db 0
dw 0xAA55

