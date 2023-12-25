#include <stdint.h>
// fix visual studio spamming errors even though its in the include path
#ifndef _MSC_VER
#include <bootboot.h>
#include <mk2/serial.h>
#include <printf.h>
#endif
#ifdef _MSC_VER
#include "../inc/bootboot.h"
#include "../inc/mk2/serial.h"
#include "../../external/printf.h"
#endif

typedef enum _MK2_STATUS {
	OK,
	ERROR,
	UNSUPPORTED,
	UNINITALIZED,
} MK2_STATUS;

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
	printf("\r\nHello, serial World!\r\n");
	return OK;
}