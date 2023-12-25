#pragma once
#include <stdint.h>
#include <stddef.h>

typedef struct _Heap_Node {
	uint32_t size;
	uint8_t used;
	struct _Heap_Node* nextNode;
	struct _Heap_Node* prevNode;
} Heap_Node;

void mem_init();

void malloc(size_t size);

void free(void* p);