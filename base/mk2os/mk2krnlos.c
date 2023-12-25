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
#endif
#ifdef _MSC_VER
#include "../inc/bootboot.h"
#include "../inc/mk2/serial.h"
#include "../../external/printf.h"
#include "../inc/mk2/mk2krnlos.h"
#include "../inc/mk2/screen/screen.h"
#include "../inc/mk2/console/console.h"
#include "../inc/mk2/mem/memory.h"
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
	return OK;
}