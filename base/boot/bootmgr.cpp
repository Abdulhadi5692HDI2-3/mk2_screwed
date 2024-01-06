#include <bootdef.h>

// gnu efi uses C declarations
// extern so the linker doesn't produce
// error: LNK2019 and LNK1120
EXTERN {
	#include <efi.h>
	#include <efilib.h>
}


EXTERN EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	Print(L"Hello World!\r\n");
	return EFI_SUCCESS;
}