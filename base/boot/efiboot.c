#include <efi.h>
#include <efilib.h>
#include <windows/types.h>
#include <windows/winnt.h>

#if defined(_M_X64) || defined(__x86_64__)
static CHAR16* ArchName = L"x86 64-bit";
#endif

EFI_FILE* LoadFile(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
	EFI_FILE* LoadedFile;
	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

	if (Directory == NULL) {
		FileSystem->OpenVolume(FileSystem, &Directory);
	}

	EFI_STATUS s = Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if (EFI_ERROR(s)) {
		return NULL;
	}
	else if (s != EFI_SUCCESS) {
		return NULL;
	}
	return LoadedFile;
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	Print(L"%s:%d", __FILE__, __LINE__);
	Print(L"MK2 Bootloader!\r\n");

	// kernel file
	EFI_FILE* Kernel = LoadFile(NULL, L"mk2krnlos.exe", ImageHandle, SystemTable);
	if (Kernel == NULL) {
		Print(L"ERROR: Could not load `mk2krnlos.exe`!\r\n");
	}
	else {
		Print(L"SUCCESS: Loaded `mk2krnlos.exe`!\r\n");
	}
	
	return EFI_SUCCESS;
}
