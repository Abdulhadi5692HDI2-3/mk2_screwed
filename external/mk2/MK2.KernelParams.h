#pragma once
#include "../gnu-efi/inc/efi.h"

typedef struct _KernelParams {
	// Runtime services
	EFI_RUNTIME_SERVICES* RT;

	// Memory Map
	EFI_MEMORY_DESCRIPTOR* MemoryMap;
	UINTN MemoryMapSz;
	UINTN MemoryMapDescriptorSz;
	UINT32 MemoryMapDescriptorVersion;
} KernelParams, *PKernelParams;