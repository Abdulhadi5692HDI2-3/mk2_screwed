org 0x7c00
BITS 16

bootmain: 
	cli
	hlt
	
times 510 - ($-$$) db 0
 
dw 0xAA55