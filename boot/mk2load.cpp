//////////////////////////////////////////
// Object output name: mk2load.obj      //
// Output name: mk2load.efi             //
// Arch: x86-64                         //
// Code written by: Abdulhadi5692HDI2-3 //
//////////////////////////////////////////

// definitions
#define EXTERNC extern "C"

#include <BootAssert.h>
// fix LNK1120 and LNK2019
EXTERNC{
#include <efi.h>
#include <efilib.h>
}

#include <win32/types.h>
#include <win32/winnt.h>

static constexpr CHAR16 KernelFName[] = L"mk2krnlos.exe";
static constexpr INT MaxKernelPathSz = 64;
EFI_MEMORY_TYPE AllocType;

EXTERNC EFI_STATUS efi_main(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable) {
	// Set the Status
	EFI_STATUS Status;
	// set ST, BS and RT variables
	ST = SystemTable;
	BS = SystemTable->BootServices;
	RT = SystemTable->RuntimeServices;

	// Initalize GNU-EFI Libary
	InitializeLib(ImageHandle, SystemTable);

	// clear the screen
	ST->ConOut->ClearScreen(ST->ConOut);

	// Display some info
	Print(L"MK2 Bootloader (original output name: mk2load.efi)\r\nFirmware vendor: %s\r\n", ST->FirmwareVendor);
	
	while (1);
	return EFI_ABORTED;
}