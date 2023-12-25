#ifndef _MSC_VER
#include <mk2/screen/screen.h>
#include <bootboot.h>
#endif
#ifdef _MSC_VER
#include "../inc/mk2/screen/screen.h"
#include "../inc/bootboot.h"
#endif

#define WHITE 0x00FFFFFF

extern uint8_t fb;
extern BOOTBOOT bootboot;

void Mk2DrawPixel(int x, int y) {
	*((uint32_t*)(&fb + bootboot.fb_scanline * y + (x) * 4)) = WHITE;
}

void Mk2DrawRect(int x, int y, int w, int h) {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			Mk2DrawPixel(x + i, y + j);
		}
	}
}