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
#include "../inc/mk2/tar/tar.h"
#endif

MK2_STATUS Mk2EntryPoint();

extern BOOTBOOT bootboot;
extern unsigned char environment[4096];
extern uint8_t fb;

void _start() {
	Mk2EntryPoint();
	while(1);
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
	return OK;
}