#ifndef _MSC_VER
#include <mk2/console/console.h>
#include <mk2/serial.h>
#endif
#ifdef _MSC_VER
#include "../inc/mk2/console/console.h"
#include "../inc/mk2/serial.h"
#endif

void _putchar(char c) {
	write_serial(c);
	// maybe write to screen here too in a function like:
	// console_putc(c);
}