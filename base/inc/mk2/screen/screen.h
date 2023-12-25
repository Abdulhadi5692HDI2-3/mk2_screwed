#pragma once
#include <stdint.h>
#include <stddef.h>
#ifndef _MSC_VER
#include <mk2/mk2krnlos.h>
#endif
#ifdef _MSC_VER
#include "../mk2krnlos.h"
#endif

void Mk2DrawPixel(int x, int y);
void Mk2DrawRect(int x, int y, int w, int h);