#define SSFN_IMPLEMENTATION
#ifndef _MSC_VER
#include <limits.h>
#include <mk2/console/console.h>
#include <mk2/serial.h>
#include <mk2/mem/memory.h>
#include <bootboot.h>
#endif
#ifdef _MSC_VER
#include <limits.h>
#include "../inc/mk2/console/console.h"
#include "../inc/mk2/serial.h"
#include "../inc/mk2/mem/memory.h"
#include "../inc/bootboot.h"
#endif


void _putchar(char c) {
	write_serial(c);
}