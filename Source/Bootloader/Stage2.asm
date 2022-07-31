;------------------------------------------------------------------------------;
; Bootloader Stage 2
;------------------------------------------------------------------------------;
[BITS 16]                              ;At this stage we are still in real mode
[ORG 0x2500]                           ;Stage 2 will be loaded to this address
                                       ; so the offset is required
%define MEMORY_MAP_ADDR 0x7E00

Stage2_Entry:                          ;Stage 2 entry point
	mov ah, 0x0E                       ;0x10 print command
	mov al, '2'                        ;'2' as an identifier
	xor bx, bx                         ;Screen 0
	int 0x10                           ;Call BIOS int 0x10

	call CreateMemoryMap               ;Call for a memory map to be created

Stage2_EnterPM:
	cli                                ;Disable interrupts before changing the
	                                   ; state of the system
	lgdt [GDT_END]                     ;Load a new GDT
	mov eax, cr0                       ;Load the cr0 register into eax
	or eax, 1                          ;Set the protected mode flag
	mov cr0, eax                       ;Load cr0 with the new value

	jmp 0x08:Stage2_Entry32            ;Jump into the 32 bit section

CreateMemoryMap:
	push bp                            ;Store bp as it will be used
	mov di, MEMORY_MAP_ADDR+4          ;Prevent E820 getting stuck - Magic
	xor ebx, ebx                       ;Clear EBX
	xor bp, bp                         ;Use bp as a counter 
	mov edx, 0x0534D4150               ;Put "SMAP" magic bytes into edx
	mov eax, 0xE820                    ;Set int 0x15 0xE820 MMAP command
	mov dword [es:di + 20], 1          ;Force ACPI 3.x entries
	mov ecx, 24                        ;Request 24 bytes
	int 0x15                           ;Call BIOS int 0x15
	jc short .failed                   ;Relative jump on failure
	mov edx, 0x0534D4150               ;Just in case edx is modified
	cmp eax, edx                       ;Successful calls set eax to "SMAP"
	jne short .failed                  ;Check failed
	test ebx, ebx                      ;If ebx == 0, only 1 entry, useless map
	je short .failed                   ;Jump to fail
	jmp short .jmpin                   ;Successful mapping
.e820lp:
	mov eax, 0xE820                    ;Reset EAX to 0x15 0xE820 MMAP command
	mov [es:di + 20], dword 1          ;Force ACPI 3.x entries
	mov ecx, 24                        ;Request 24 bytes
	int 0x15                           ;Call BIOS int 0x15
	jc short .e820f                    ;Carry set, end of mmap list
	mov edx, 0x0534D4150               ;Rset EDX to "SMAP" value
.jmpin:
	jcxz .skipent                      ;Skip null entries
	cmp cl, 20                         ;Check the response was 24 byte ACPI 3.x
	jbe short .notext                  ;Not ACPI 3.x response
	test byte [es:di+20], 1            ;Test ignore bit
	je short .skipent                  ;Skip if ignore bit set
.notext:
	mov ecx, dword [es:di+8]           ;Get lower bound
	or ecx, [es:di+12]                 ;Test for zero length entries
	jz .skipent                        ;Skip zero length entries
	inc bp                             ;Increment counter
	add di, 24                         ;Increment destination
.skipent:
	test ebx, ebx                      ;Test ebx == zero
	jne short .e820lp                  ;Not equal, get next entry
.e820f:
	mov word [MEMORY_MAP_ADDR], bp     ;Store the counter
	clc                                ;Clear the carry flag
	pop bp                             ;Restore bp value
	ret                                ;Return
.failed:
	stc                                ;Set carry fail condition
	pop bp                             ;Restore bp
	ret                                ;Return

Stage2_Halt:                           ;Stage 2 halt routine
	cli                                ;Disable interrupts
	hlt                                ;Halt the CPU
	jmp Stage2_Halt                    ;Just in case the CPU is woken up


GDT:                                   ;GDT, a magic data structure relating to
GDT_NULL:                              ; memory layout
	dq 0                               ;Always starts with a null entry
GDT_CODE:                              ;Code entry for a flat memory model
	dw 0xFFFF
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0
GDT_DATA:                              ;Data entry for a flat format
	dw 0xFFFF
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0
GDT_END:                               ;Calculated memory position for lgdt
dw GDT_END-GDT-1
dd GDT


;------------------------------------------------------------------------------;
; The 32 bit world is much friendlier,
; C can be used for most of the 32 bit world
;------------------------------------------------------------------------------;
[BITS 32]

Stage2_Entry32:                        ;32 bit entry point, interrupts are
                                       ; disabled at this point
	mov ax, 0x10                       ;Reset all segment registers using 0x10
	mov ds, ax                         ; as per the GDT
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	call EnableA20                     ;Enable the A20 addressing line

	sti                                ;Enable interrupts

	mov byte [0xB8008], '3'            ;Write to character 8 of the video memory
	mov byte [0xB800A], '2'            ;Write to character 10 of the video mem

	jmp 0x2700

Stage2_Halt32:                         ;32 bit halt routine
	cli                                ;Disable interrupts
	hlt                                ;Halt the CPU
	jmp Stage2_Halt32                  ;Just in case we wake up

EnableA20:                             ;The A20 addressing line needs to be
                                       ; enabled to access the "higher memory"
									   ; regions, this is done using the
									   ; keyboard controller.
									   ; Interrupts must be off
	call A20Wait
	mov al, 0xAD
	out 0x64, al

	call A20Wait
	mov al, 0xD0
	out 0x64, al

	call A20Wait2
	in al, 0x60
	push eax

	call A20Wait
	mov al, 0xD1
	out 0x64, al

	call A20Wait
	pop eax
	or al, 2
	out 0x60, al

	call A20Wait
	mov al, 0xAE
	out 0x64, al

	call A20Wait
	ret

A20Wait:
	in al, 0x64
	test al, 2
	jnz A20Wait
	ret

A20Wait2:
	in al, 0x64
	test al, 1
	jz A20Wait2
	ret
