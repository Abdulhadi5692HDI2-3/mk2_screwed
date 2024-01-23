; Module name: bootparameterblock.inc
;
; Abstract:
;   Boot parameter block for floppy disk
;
; Author: Abdulhadi5692HDI2-3
; Copyright (c) Abdulhadi5692HDI2-3 2024
;
; Licensed under MIT License;

; OEM Parameter block
; STARTOEMBLOCK
	OSName			  db "MSWIN"
	OSVersion         db "4.1"      ; Version number
	
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