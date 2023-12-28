#ifndef _MSC_VER
#include <mk2/interrupts/idt.h>
#endif
#ifdef _MSC_VER
#include "../inc/mk2/interrupts/idt.h"
#endif


IDT_VOID SetOffset(IDTEntry* entry, uint64_t offset) {
	entry->offset0 = (uint16_t)(offset & 0x000000000000ffff);
	entry->offset1 = (uint16_t)((offset & 0x00000000ffff0000) >> 16);
	entry->offset2 = (uint32_t)((offset & 0xffffffff00000000) >> 32);
}

IDT_UINT64 GetOffset(IDTEntry* entry) {
	IDT_UINT64 offset = 0;
	offset |= (IDT_UINT64)entry->offset0;
	offset |= (IDT_UINT64)entry->offset1 << 16;
	offset |= (IDT_UINT64)entry->offset2 << 32;
	return offset;
}


IDT_VOID init_idt() {

}