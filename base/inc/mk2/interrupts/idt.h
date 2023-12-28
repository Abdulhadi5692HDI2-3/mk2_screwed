#pragma once
#include <stdint.h>

#define IDT_TA_InterruptGate	0b10001110
#define IDT_TA_CallGate			0b10001100
#define IDT_TA_TrapGate			0b10001111

#define IDT_VOID				void
#define IDT_UINT64				uint64_t

typedef struct _IDTEntry {
	uint16_t offset0;
	uint16_t selector;
	uint8_t ist;
	uint8_t type_attr;
	uint16_t offset1;
	uint32_t offset2;
	uint32_t ignore;
} IDTEntry;

#ifndef _MSC_VER
typedef struct _IDTR {
	uint16_t limit;
	uint64_t offset;
} __attribute__((packed)) IDTR;
#endif

#ifdef _MSC_VER
__pragma(pack(push, 1));
typedef struct _IDTR {
	uint16_t limit;
	uint64_t offset;
}IDTR;
__pragma(pack(pop));
#endif

IDT_VOID SetOffset(IDTEntry* entry, uint64_t offset);
IDT_UINT64 GetOffset(IDTEntry* entry);