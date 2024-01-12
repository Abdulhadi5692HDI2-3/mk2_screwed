//////////////////////////////////////////
// Object output name: mk2load.obj      //
// Output name: mk2load.efi             //
// Arch: x86-64                         //
// Code written by: Abdulhadi5692HDI2-3 //
//////////////////////////////////////////

// definitions
#define EXTERNC extern "C"

// fix LNK1120 and LNK2019
EXTERNC{
	#include <efi.h>
	#include <efilib.h>
}

EXTERNC EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	// set ST, BS and RT variables
	ST = SystemTable;
	BS = SystemTable->BootServices;
	RT = SystemTable->RuntimeServices;

	// Initalize GNU-EFI Libary
	InitializeLib(ImageHandle, SystemTable);

	// clear the screen
	ST->ConOut->ClearScreen(ST->ConOut);

	// Display some crap
	Print(L"MK2 Bootloader (original output name: mk2load.efi)\r\n");
	while (1);
	return EFI_ABORTED;
}