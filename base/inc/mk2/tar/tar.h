#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct _TarHdr {
	char filename[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag[1];
} TarHdr;

typedef unsigned int TAR_UINT;
TAR_UINT totalfiles(TAR_UINT ptr);