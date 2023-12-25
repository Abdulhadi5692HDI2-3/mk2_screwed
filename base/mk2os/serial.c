#ifndef _MSC_VER
#include <mk2/serial.h>
#include <mk2/ioasm.h>
#endif
#ifdef _MSC_VER
#include "../inc/mk2/serial.h"
#include "../inc/mk2/ioasm.h"
#endif

int serial_received() {
	return inb(0x3f8 + 5) & 1;
}

char read_serial() {
	while (serial_received() == 0);
	return inb(0x3f8);
}

int is_transmit_empty() {
	return inb(0x3f8 + 5) & 0x20;
}

void write_serial(char a) {
	while (is_transmit_empty() == 0);
	outb(0x3f8, a);
}