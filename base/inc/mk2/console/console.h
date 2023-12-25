#pragma once
#include <stdint.h>

#define PSF_FONT_MAGIC 0x864ab572

#ifndef _MSC_VER
typedef struct {
	uint32_t magic;
	uint32_t version;
	uint32_t headersize;
	uint32_t flags;
	uint32_t numglyph;
	uint32_t bytesperglyph;
	uint32_t height;
	uint32_t width;
	uint8_t glyphs;
} __attribute__((packed)) psf2_t;
#endif
#ifdef _MSC_VER

#pragma pack(push)
#pragma pack(1)
typedef struct {
	uint32_t magic;
	uint32_t version;
	uint32_t headersize;
	uint32_t flags;
	uint32_t numglyph;
	uint32_t bytesperglyph;
	uint32_t height;
	uint32_t width;
	uint8_t glyphs;
} psf2_t;
#pragma pack(pop)
#endif

// Console interface
// implements _putchar() for external/printf.c
void _putchar(char);