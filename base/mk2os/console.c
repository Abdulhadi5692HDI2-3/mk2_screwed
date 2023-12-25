#ifndef _MSC_VER
#include <mk2/console/console.h>
#include <mk2/serial.h>
#include <bootboot.h>
#endif
#ifdef _MSC_VER
#include "../inc/mk2/console/console.h"
#include "../inc/mk2/serial.h"
#include "../inc/bootboot.h"
#endif

extern volatile unsigned char _binary_fonts_font_psf_start;
extern volatile unsigned char _binary_fonts_font_psf_end;

uint16_t *unicode;
extern uint8_t fb;
extern BOOTBOOT bootboot;

void psf_putc(char c) {
	
}


void _putchar(char c) {
	write_serial(c);
}