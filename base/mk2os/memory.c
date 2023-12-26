#ifndef _MSC_VER
#include <mk2/mem/memory.h>
#endif
#ifdef _MSC_VER
#include "../inc/mk2/mem/memory.h"
#endif

#define HEAP_TOTAL_SIZE       4*1024
#define HEAP_NODE_SIZE        sizeof(Heap_Node)

static unsigned char HeapArea[HEAP_TOTAL_SIZE];
static Heap_Node* heapStart = (Heap_Node*)HeapArea;

void mem_init() {
	heapStart = (Heap_Node*)HeapArea;
	heapStart->size = HEAP_TOTAL_SIZE - HEAP_NODE_SIZE;
	heapStart->nextNode = NULL;
	heapStart->prevNode = NULL;
}

void *memcpy(void *dest, const void *src, size_t n) {
	uint8_t *pdest = (uint8_t *)dest;
	const uint8_t *psrc = (const uint8_t *)src;

	for (size_t i = 0; i < n; i++) {
		pdest[i] = psrc[i];
	}

	return dest;
}

void *memset(void *s, int c, size_t n) {
	uint8_t *p = (uint8_t *)s;

	for (size_t i = 0; i < n; i++) {
		p[i] = (uint8_t)c;
	}

	return s;
}

void *memmove(void *dest, const void *src, size_t n) {
	uint8_t *pdest = (uint8_t *)dest;
	const uint8_t *psrc = (const uint8_t *)src;

	if (src > dest) {
		for (size_t i = 0; i < n; i++) {
			pdest[i] = psrc[i];
		}
	}
	else if (src < dest) {
		for (size_t i = n; i > 0; i--) {
			pdest[i - 1] = psrc[i - 1];
		}
	}

	return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
	const uint8_t *p1 = (const uint8_t *)s1;
	const uint8_t *p2 = (const uint8_t *)s2;

	for (size_t i = 0; i < n; i++) {
		if (p1[i] != p2[i]) {
			return p1[i] < p2[i] ? -1 : 1;
		}
	}

	return 0;
}

void* malloc(size_t size) {
	Heap_Node* currentHeapBlock;
	Heap_Node* bestHeapBlock;
	uint32_t bestHeapBlockSize;

	currentHeapBlock = heapStart;
	bestHeapBlock = (Heap_Node*)NULL;
	bestHeapBlockSize = HEAP_TOTAL_SIZE + 1;
	while (currentHeapBlock) {
		if ((!currentHeapBlock->used) && (currentHeapBlock->size >= (size + HEAP_NODE_SIZE)) && (currentHeapBlock->size <= bestHeapBlockSize)) {
			bestHeapBlock = currentHeapBlock;
			bestHeapBlockSize = currentHeapBlock->size;
		}
		currentHeapBlock = currentHeapBlock->nextNode;
	}

	if (bestHeapBlock != NULL) {
		Heap_Node* heapNodeAllocate;

		bestHeapBlock->size = bestHeapBlock->size - size - HEAP_NODE_SIZE;
		heapNodeAllocate = (Heap_Node*)(((unsigned char*)bestHeapBlock) + HEAP_NODE_SIZE + bestHeapBlock->size);
		heapNodeAllocate->size = size;
		heapNodeAllocate->used = 1;
		heapNodeAllocate->nextNode = bestHeapBlock->nextNode;
		heapNodeAllocate->prevNode = bestHeapBlock;
		if (bestHeapBlock->nextNode != NULL) {
			bestHeapBlock->nextNode->prevNode = heapNodeAllocate;
		}
		bestHeapBlock->nextNode = heapNodeAllocate;
		return (void*)((unsigned char*)heapNodeAllocate + HEAP_NODE_SIZE);
	}

	return NULL;
}

void free(void* p) {
	if (p == NULL) {
		return;
	}
	Heap_Node* currentBlock = (Heap_Node*)((unsigned char*)p - HEAP_NODE_SIZE);

	if (currentBlock == NULL) {
		return;
	}
	currentBlock->used = 0;

	if (currentBlock->nextNode != NULL) {
		if (!currentBlock->nextNode->used) {
			currentBlock->size += currentBlock->nextNode->size;
			currentBlock->size += HEAP_NODE_SIZE;
			currentBlock->nextNode = currentBlock->nextNode->nextNode;

			if (currentBlock->nextNode != NULL) {
				currentBlock->nextNode->prevNode = currentBlock;
			}
		}
	}


	if (currentBlock->prevNode != NULL) {
		if (!currentBlock->prevNode->used) {
			currentBlock->prevNode->size += currentBlock->size;
			currentBlock->prevNode->size += HEAP_NODE_SIZE;
			currentBlock->prevNode->nextNode = currentBlock->nextNode;
			if (currentBlock->nextNode != NULL) {
				currentBlock->nextNode->prevNode = currentBlock->prevNode;
			}
		}
	}
}


void* realloc(void* ptr, size_t size) {
	void* p;
	p = malloc(size);
	if (p == NULL) {
		return p;
	}

	if (ptr != NULL) {
		size_t sizeToCopy;
		size_t originalSize = ((Heap_Node*)((unsigned char*)ptr - HEAP_NODE_SIZE))->size;

		if (originalSize < size) {
			sizeToCopy = originalSize;
		}
		else {
			sizeToCopy = size;
		}
		memcpy(p, ptr, sizeToCopy);
		free(ptr);
	}
	return p;
}

void* calloc(size_t num, size_t size) {
	void* p;
	size_t sizeInBytes;

	sizeInBytes = num * size;
	p = malloc(sizeInBytes);
	if (p != NULL) {
		memset(p, 0, sizeInBytes);
	}
	return p;
}