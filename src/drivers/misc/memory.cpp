/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <memory.hpp>
#include <types.hpp>

#define MEMORY_POOL_SIZE 1024 * 1024

typedef struct MemoryBlock {
    size_t Size;
    struct MemoryBlock *Next;
    int Free;
} MemoryBlockT;

static uint8_t memoryPool[MEMORY_POOL_SIZE];
static MemoryBlockT *freeList = (MemoryBlockT *)memoryPool;

void InitMemory() {
    freeList->Size = MEMORY_POOL_SIZE - sizeof(MemoryBlockT);
    freeList->Next = nullptr;
    freeList->Free = 1;
}

extern "C" void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *malloc(size_t size) {
    MemoryBlockT *current = freeList;
    while (current != NULL) {
        if (current->Free && current->Size >= size) {
            if (current->Size > size + sizeof(MemoryBlockT)) {
                MemoryBlockT *newBlock = (MemoryBlockT *)((uint8_t *)current + sizeof(MemoryBlockT) + size);
                newBlock->Size = current->Size - size - sizeof(MemoryBlockT);
                newBlock->Next = current->Next;
                newBlock->Free = 1;

                current->Size = size;
                current->Next = newBlock;
            }
            current->Free = 0;
            return (void *)((uint8_t *)current + sizeof(MemoryBlockT));
        }
        current = current->Next;
    }
    return NULL;
}

void free(void *ptr) {
    if (ptr == NULL) return;

    MemoryBlockT *block = (MemoryBlockT *)((uint8_t *)ptr - sizeof(MemoryBlockT));
    block->Free = 1;

    if (block->Next != NULL && block->Next->Free) {
        block->Size += sizeof(MemoryBlockT) + block->Next->Size;
        block->Next = block->Next->Next;
    }

    MemoryBlockT *current = freeList;
    while (current != NULL) {
        if (current->Next == block && current->Free) {
            current->Size += sizeof(MemoryBlockT) + block->Size;
            current->Next = block->Next->Next;
            break;
        }
        current = current->Next;
    }
}

extern "C" void *memset(void *s, int c, size_t n) {
    unsigned char *ptr = (unsigned char *)s;
    while (n--) {
        *ptr++ = (unsigned char)c;
    }
    return s;
}

void *operator new(size_t size) { return malloc(size); }

void *operator new[](size_t size) { return malloc(size); }

void operator delete(void *ptr) noexcept { free(ptr); }

void operator delete[](void *ptr) noexcept { free(ptr); }