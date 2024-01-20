; Module name: boot.asm
;
; Abstract:
;   * Load the Stage 2 bootloader
;   * Prepare the environment for the Stage 2 bootloader
;
; Author: Abdulhadi5692HDI2-3
; Copyright (c) Abdulhadi5692HDI2-3 2024
;
; Licensed under MIT License;

; we are in 16 bit mode
code segment

assume cs:code
; we (should) be loaded at 0x7c00
org 7c00h

start: jmp astart

; OEM Parameter block
; STARTOEMBLOCK
    OEMName	          db "BOOT    " ; Disk label
    bytesPerSector    dw 512	    ; Bytes per sector
    sectorsPerCluster db 1			; Sectors per cluster
    reservedSectors   dw 1			; Reserved sectors
    fats	          db 2			; Number of fats
    rootDirEntries    dw 224	    ; Number of entries in root dir
    sectors	          dw 2880	    ; Logical sectors
    mediaType	      db 0f0h       ; Media descriptor byte
    fatSectors        dw 9			; Sectors per FAT
    sectorsPerTrack   dw 18			; Sectors per track
    heads	          dw 2			; Number of sides/heads
    hiddenSectors     dd 0			; Hidden sectors
    hugeSectors	      dd 0			; LBA sectors
    biosDriveNum      db 0			; Drive number
    reserved	      db 0			; Reserved
    bootSignature     db 41			; Drive signature
    volumeId	      dd 0			; Volume ID
    volumeLabel	      db "BOOT VOLUME" ; Volume Label
    fatTypeLabel      db "FAT12   "	   ; File system type
; ENDOEMBLOCK

astart:
	main:
		mov ax, 0000h ; setup the data segment register
		mov ds, ax ; We cannot do `mov ds, 0000h` due to limitations
		           ; on the CPU.
		
		mov si, offset hiworld ; Load the string into the si register to print to the screen.
		call BootPutString ; Call the put string function.
		jmp $ ; Loop forever

; Procedures (labels in NASM)
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

; Strings and data
hiworld db 'Hello World', 13, 10, 0

; End of St1 boot program
db 510-($-start) dup(0) ; Fill rest of the sectors with zeroes
dw 0AA55h ; Boot signature for BIOS
code ends
end start