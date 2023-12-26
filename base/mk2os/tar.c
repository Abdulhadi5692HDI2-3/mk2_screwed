#ifndef _MSC_VER
#include <mk2/tar/tar.h>
#include <printf.h>
#endif
#ifdef _MSC_VER
#include "../inc/mk2/tar/tar.h"
#include "../../external/printf.h"
#endif


TarHdr *headers[32];

static TAR_UINT tar_getsize(const char* in) {
	TAR_UINT size = 0;
	TAR_UINT j;
	TAR_UINT count = 1;

	for (j = 11; j > 0; j--, count *= 8) {
		size += ((in[j - 1] - '0') * count);
	}
	return size;
}

/* oh god please dont use such code again.
TAR_UINT tar_size(TAR_UINT ptr) {
	TAR_UINT i;
	TAR_UINT size;
	for (i = 0;; i++) {
		TarHdr *hdr = (TarHdr*)ptr;
		if (hdr->filename[0] == '\0') {
			break;
		}
		size = tar_getsize(hdr->size);
	}
	return size;
}
*/

TAR_UINT totalfiles(TAR_UINT ptr) {
	TAR_UINT i;
	for (i = 0;; i++) {
		TarHdr *hdr = (TarHdr*)ptr;
		if (hdr->filename[0] == '\0') {
			break;
		}
		TAR_UINT size = tar_getsize(hdr->size);
		printf("Found file %s!\r\nSize: %d bytes.\r\n", hdr->filename, size);
		headers[i] = hdr;
		ptr += ((size / 512) + 1) * 512;
		if (size % 512) {
			ptr += 512;
		}
	}
	return i;
}
