; Module name: mk2ldr.asm
;
; Abstract: 
;  	 Stage 2 bootloader executed by stage 1.
;    * Load the Kernel
;    * Switch into 32 bits (protected mode)
;    * Prepare the environment for the kernel. (protected mode, A20 line etc.)
;
; Author: Abdulhadi5692HDI2-3
; Copyright (c) Abdulhadi5692HDI2-3 2024
; Licensed under MIT License

; Here we are being executed like a 16 bit COM program
; So we are still in 16 bit mode
; BUT we are still in ring 0
; so we still have control over the computer
code segment

assume cs:code

; offset to 0 since we are settings registers later
org 0h

; we are loaded at linear address 0x10000

start: jmp main


; Abstract: Put a string from the [SI] register onto the screen
; Origin File: boot.asm
BootPutString:
	; Here we setup up the registers for the int 10 interrupt
	mov ah, 0Eh ; Tell the BIOS that we want to be in teletype mode
	mov bh, 00h ; Page number
	mov bl, 07h ; Normal text attribute
	
	.nextchar:
		lodsb ; Load [SI] into [AL] and increase [SI] by 1
	
	or al, al ; Check for end of string.(this checks if al = 0)
			  ; If it is zero it sets the zero flag in the register
			  ; C code: if (al == 0) { zeroflag = true; goto return; }
	jz return ; if zero then just stop
	int 10h ; BIOS video/teletype interrupt
	jmp .nextchar
	return:
	ret


; Entry point for stage 2
; Abstract: Entry point
main:
	sti     ; Set the interrupt flag
	push cs ; Insure DS=CS
	pop ds
	
	mov si, offset PrepMsg
	call BootPutString
	
	cli     ; Clear interrupts to prevent triple-fault
	hlt     ; Halt the system


PrepMsg db 'MK2LDR: Preparing to load MK2 kernel', 13, 10, 0
code ends
end start