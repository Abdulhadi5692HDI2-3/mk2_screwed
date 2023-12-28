#include <stdint.h>
// fix visual studio spamming errors even though its in the include path
#ifndef _MSC_VER
#include <bootboot.h>
#include <mk2/serial.h>
#include <printf.h>
#include <mk2/mk2krnlos.h>
#include <mk2/screen/screen.h>
#include <mk2/console/console.h>
#include <mk2/mem/memory.h>
#include <mk2/interrupts/idt.h>
#include <mk2/interrupts/interrupt.h>
#include <mk2/tar/tar.h>
#endif
#ifdef _MSC_VER
#include "../inc/bootboot.h"
#include "../inc/mk2/serial.h"
#include "../../external/printf.h"
#include "../inc/mk2/mk2krnlos.h"
#include "../inc/mk2/screen/screen.h"
#include "../inc/mk2/console/console.h"
#include "../inc/mk2/mem/memory.h"
#include "../inc/mk2/interrupts/idt.h"
#include "../inc/mk2/interrupts/interrupt.h"
#include "../inc/mk2/tar/tar.h"
#endif

MK2_STATUS Mk2EntryPoint();

// this has to be here.
// we dont have to write the init stuff in here though.
void _start() {
	Mk2EntryPoint();
	while (1);
}

// global variables
// and stuff from the bootloader.
extern BOOTBOOT bootboot;
extern unsigned char environment[4096];
extern uint8_t fb;


IDTR idtr;


MK2_STATUS Mk2PrepInterrupts() {
	idtr.limit = 0x0FFF;
	// allocate some memory for the idtr register
	idtr.offset = (uint64_t)malloc(sizeof(idtr));
	if (idtr.offset == NULL) {
		return ERROR;
	}
	IDTEntry* pagefault = (IDTEntry*)(idtr.offset + 0x0E * sizeof(IDTEntry));
	SetOffset(pagefault, (uint64_t)PageFault_Handler);
	pagefault->type_attr = IDT_TA_InterruptGate;
	pagefault->selector = 0x08;

	__asm__("lidt %0" : : "m" (idtr));
	__asm__("sti");
	return OK;
}
// printf just prints to the serial port for now!
MK2_STATUS Mk2EntryPoint() {
	printf("Hello World!\r\n");
	printf("Screen Resolution: %dx%d\r\n", bootboot.fb_width, bootboot.fb_height);
	mem_init();
	printf("Initalized the heap!\r\n");
	// totalfiles returns how many files are there
	// in a tar file. (in our case the initrd)
	printf("Total files in initrd: %d\r\n", totalfiles(bootboot.initrd_ptr));
	printf("Testing memory allocation!\r\n");
	int a = malloc(32);
	printf("Allocated 32 bytes for variable 'a'.\r\nAddress: 0x%x\r\nValue: %d\r\n", &a, a);
	free(a);
	Mk2PrepInterrupts();
	__asm__("int $0x0e");
	return OK;
}