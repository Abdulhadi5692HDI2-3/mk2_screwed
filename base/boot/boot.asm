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


; code segment
code segment

assume cs:code


; 
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
		
		mov si, offset real16boot ; Load the string into the si register to print to the screen.
		call BootPutString ; Call the put string function.
		
		


; Stuff right after the bootloader starts

; <empty>	
	
; Functions

; Abstract: Puts a string from the [SI] register onto the screen
BootPutString PROC USES si
	; Here we setup up the registers for the int 10 interrupt
	mov ah, 0Eh ; Tell the BIOS that we want to be in teletype mode
	mov bh, 00h ; Page number
	mov bl, 07h ; Normal text attribute
	
	.nextchar:
		lodsb ; Load [SI] into [AL] and increase [SI] by 1
	
	or al, al ; Check for end of string.(this checks if al = 0)
			  ; If it is zero it sets the zero flag in the register
			  ; C code: if (al == 0) { zeroflag = true; goto return; } return: /* nothing */
	jz return ; if zero then just stop
	int 10h ; BIOS video/teletype interrupt
	jmp .nextchar
	return:
	ret
BootPutString ENDP
; Disk functions (args predefined)

; Abstract: Reset reading from floppy drive 0. (this goes back to sector 1)
DiskReset PROC
	mov ah, 0 ; Status code
	mov dl, 0 ; Carry flag (clear if success, set if failure)
	int 13h   ; BIOS Disk interrupt
	jc DiskReset ; If the Carry Flag is set, then try again
DiskReset ENDP

; Abstract: Read the 2nd sector of the floppy
DiskRead PROC
	mov ah, 02h ; to read this must be 02h by default
	mov al, 1   ; Number of sectors to read. In this case we are reading 1
	mov ch, 1   ; Low 8 bits of cylinder number. We are reading the second sector past us.
	mov cl, 2   ; The sector to read. In our case, sector 2
	mov dh, 0   ; Head number
	mov dl, 0   ; Drive number. Drive 0 is our floppy drive.
	int 13h     ; BIOS Disk interrupt
	jc DiskRead ; If there is an error then try again
DiskRead ENDP

; Strings and data
absoluteSector db 00h
absoluteHead db 00h
absoluteTrack db 00h

datasector dw 0000h
cluster dw 0000h
startofroot dw 0000h
numberofroot dw 0000h
userData dw 0000h

ImageName db "MK2LDR_ SYS"
real16boot db 'MK2 STAGE 1 BOOTLOADER. LOADING A:\\MK2LDR_.SYS . . .', 13, 10, 0
errmsg db 'Error! Could not find MK2LDR_.SYS! Aborting. . .', 13 , 10, 0
_crlf db 13, 10, 0

db 510-($-start) dup(0) ; Fill rest of the sectors with zeroes
dw 0AA55h ; Boot signature for BIOS

code ends
end start