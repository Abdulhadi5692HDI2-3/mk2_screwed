; Module name: boot.asm
;
; Abstract:
;   Stage 1 bootloader executed by the BIOS
;   * Load the Stage 2 bootloader
;   * Prepare the environment for the Stage 2 bootloader
;
; Author: Abdulhadi5692HDI2-3
; Copyright (c) Abdulhadi5692HDI2-3 2024
;
; Licensed under MIT License;



; 386 cpu
.386
	option segment:use16 ; 16 bits !!!
.model tiny


.code
BOOTORIGIN equ 7C00H

; we (should) be loaded at 0x7c00
org BOOTORIGIN

start: 
	jmp short astart
	nop

include W:\base\boot\bootparameterblock.inc

astart:
	main:
		cli
		xor ax, ax ; Location of the boot loader divided by 16
		mov ds, ax ; Set data segment to where we are loaded.
		add ax, 20h ; Skip over the size of the bootloader divided by 16 (512 / 16)
		mov ss, ax ; Set segment register to current location (start of stack)
		mov sp, 4096 ; Set ss:sp to the top of the 4k stack.
		sti
		
		mov [biosDriveNum], dl ; Store bootdrive number
		
		mov si, offset startup ; Load the string into the si register to print to the screen.
		call BootPutString ; Call the put string function.
		cli
		hlt
	
; Functions
 
; Abstract: Puts a string from the [SI] register onto the screen
BootPutString PROC
	; Here we setup up the registers for the int 10 interrupt
	mov ah, 0Eh ; Tell the BIOS that we want to be in teletype mode
	mov bh, 00h ; Page number
	mov bl, 07h ; Normal text attribute
	
	@@_loop:
		lodsb ; Load [SI] into [AL] and increase [SI] by 1
	
	or al, al ; Check for end of string.(this checks if al = 0)
			  ; If it is zero it sets the zero flag in the register
			  ; C code: if (al == 0) { zeroflag = true; goto return; } return: /* nothing */
	jz return ; if zero then just stop
	int 10h ; BIOS video/teletype interrupt
	jmp @@_loop
	return:
	ret
BootPutString ENDP

startup db 'MK2 Bootloader. Preparing. . ', 13, 10, 0 
byte 510 - ($ - start) dup (0)
dw 0AA55h ; Boot signature for BIOS
END start