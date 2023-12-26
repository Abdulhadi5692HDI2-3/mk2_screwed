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

void *memcpy(void *dest, const void *src, size_t n);

void *memset(void *s, int c, size_t n);

void *memmove(void *dest, const void *src, size_t n);

int memcmp(const void *s1, const void *s2, size_t n);

void* malloc(size_t size);

void free(void* p);

void* realloc(void* ptr, size_t size);

void* calloc(size_t num, size_t size);