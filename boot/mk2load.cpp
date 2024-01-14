//////////////////////////////////////////
// Object output name: mk2load.obj      //
// Output name: mk2load.efi             //
// Arch: x86-64                         //
// Code written by: Abdulhadi5692HDI2-3 //
//////////////////////////////////////////

#include <mk2/MK2.Defs.h>
// useful assert
#include <BootAssert.h>

// fix LNK1120 and LNK2019
EXTERNC {
#include <efi.h>
#include <efilib.h>
}

#include <win32/types.h>
#include <win32/winnt.h>

// variables
BOOLEAN is_uefienv = true;
static constexpr CHAR16 KernelFName[] = L"mk2krnlos.exe";
static constexpr INT MaxKernelPathSz = 64;

EFI_MEMORY_TYPE AllocType;

// returns volume
// which has a read / close / open abstraction
OUT EFI_FILE_HANDLE OpenVolume(IN EFI_HANDLE ImageHandle) {
	EFI_LOADED_IMAGE *LoadedImage = NULL;
	EFI_GUID LoadedImageProtGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
	EFI_FILE_IO_INTERFACE *InOutVol;
	EFI_GUID FileSystemGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	EFI_FILE_HANDLE Volume;

	BS->HandleProtocol(ImageHandle, &LoadedImageProtGuid, (VOID**)&LoadedImage);
	BS->HandleProtocol(LoadedImage->DeviceHandle, &FileSystemGuid, (VOID**)&InOutVol);
	InOutVol->OpenVolume(InOutVol, &Volume);
	return Volume;
}

// returns a pointer to the entry point
// very useful
OUT PVOID LoadPE(IN CHAR16 *fname, IN EFI_HANDLE ImageHandle, OUT EFI_PHYSICAL_ADDRESS ImageBaseOut) {
	BootAssert(is_uefienv);
	
	EFI_FILE_HANDLE Volume = OpenVolume(ImageHandle);
	EFI_FILE_HANDLE FileHandle;
	EFI_STATUS Status = Volume->Open(Volume, &FileHandle, fname, EFI_FILE_MODE_READ, 0);
	if (Status != EFI_SUCCESS) {
		Print(L"FATAL: %s:%d: Could not open file %s. Return code: %r\r\n", __FILEW__, __LINE__, fname, Status);
		return NULL;
	}
	else {
		Print(L"SUCCESS: Opened file %s\r\nContinuing. . \r\n", fname);
	}

	IMAGE_DOS_HEADER DOSHeader;
	UINTN Size = sizeof(IMAGE_DOS_HEADER);
	FileHandle->Read(FileHandle, &Size, (VOID*)&DOSHeader);

	// print magic and lfanew
	Print(
		L"e_magic = 0x%x\r\n"
		L"e_lfanew = 0x%x\r\n", 
		DOSHeader.e_magic, 
		DOSHeader.e_lfanew
	);

	// validate dos header
	BootAssert_True_Msg(DOSHeader.e_magic != IMAGE_DOS_SIGNATURE, L"Invalid DOS Header magic!\r\n");

	FileHandle->SetPosition(FileHandle, (UINT64)DOSHeader.e_lfanew);
	IMAGE_NT_HEADERS64 NTHeader;
	Size = sizeof(IMAGE_NT_HEADERS64);
	FileHandle->Read(FileHandle, &Size, (VOID*)&NTHeader);

	// print signature and optional header -> magic
	Print(
		L"Signature = 0x%x\r\n"
		L"OptionalHeader->Magic = 0x%x\r\n",
		NTHeader.Signature,
		NTHeader.OptionalHeader.Magic
	);

	// validate nt header and optional header
	// also validate subsystem
	BootAssert_True_Msg(NTHeader.Signature != IMAGE_NT_SIGNATURE
						|| NTHeader.OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC
						|| NTHeader.OptionalHeader.Subsystem != IMAGE_SUBSYSTEM_NATIVE, 
					    L"Invalid NT Header signature, Optional Header magic and Subsystem!\r\n");

	// ok so now we have validated the NT Header
	// check if kernel imports any external DLL
	BootAssert_True_Msg(NTHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size != 0, L"Kernel can't import external DLLs yet!\r\n");

	// now is a good time to allocate pages
	// for the full image
	BS->AllocatePages(AllocateAnyPages, EfiLoaderData, EFI_SIZE_TO_PAGES((UINTN)NTHeader.OptionalHeader.SizeOfImage), &ImageBaseOut);

	// ok now read more headers into memory
	Size = NTHeader.OptionalHeader.SizeOfHeaders;
	FileHandle->SetPosition(FileHandle, 0);
	FileHandle->Read(FileHandle, &Size, (VOID*)ImageBaseOut);

	// pointer the NTHeader in memory
	PIMAGE_NT_HEADERS64 PointerNTHeader = (PIMAGE_NT_HEADERS64)(ImageBaseOut + DOSHeader.e_lfanew);

	// writing sections into memory
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(PointerNTHeader);
	for (WORD i = 0; i < PointerNTHeader->FileHeader.NumberOfSections; i++) {
		EFI_PHYSICAL_ADDRESS destination = ImageBaseOut + section[i].VirtualAddress;

		UINTN rawSize = section[i].SizeOfRawData;
		if (rawSize != 0) {
			FileHandle->SetPosition(FileHandle, section[i].PointerToRawData);
			FileHandle->Read(FileHandle, &rawSize, (VOID*)destination);
		}
	}
	// do we need to relocate
	bool DoWeNeedToRelocate = PointerNTHeader->OptionalHeader.ImageBase != BaseAddress;

	// update nt header image base
	PointerNTHeader->OptionalHeader.ImageBase = BaseAddress;
	// print whether we need to relocate
	Print(L"Relocate?: %d (1 = true, 0 = false)\r\n", DoWeNeedToRelocate);
	return NULL;
}
EXTERNC EFI_STATUS efi_main(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable) {
	// Set the Status
	EFI_STATUS Status;
	
	// 
	EFI_PHYSICAL_ADDRESS IBOut;

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
	PVOID a = LoadPE(L"krnl.exe", ImageHandle, IBOut);
	while (1);
	return EFI_ABORTED;
}