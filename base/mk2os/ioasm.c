#ifndef _MSC_VER
#include <mk2/ioasm.h>
#endif
#ifdef _MSC_VER
// FIXMEURGENTLY: this is holy terrible
#define asm _asm
#include "../inc/mk2/ioasm.h"
#endif

 void outb(uint16_t port, uint8_t val) {
	asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

 uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

 void io_wait(void) {
	outb(0x80, 0);
}