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
    struct MemoryBlock* Next;
    int Free;
} MemoryBlock;

static uint8 memoryPool[MEMORY_POOL_SIZE];
static MemoryBlock* freeList = (MemoryBlock*)memoryPool;

void InitMemory() {
    freeList->Size = MEMORY_POOL_SIZE - sizeof(MemoryBlock);
    freeList->Next = nullptr;
    freeList->Free = 1;
}

extern "C" void* memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void* malloc(size_t size) {
    MemoryBlock* current = freeList;
    while (current != NULL) {
        if (current->Free && current->Size >= size) {
            if (current->Size > size + sizeof(MemoryBlock)) {
                MemoryBlock* newBlock = (MemoryBlock*)((uint8*)current + sizeof(MemoryBlock) + size);
                newBlock->Size = current->Size - size - sizeof(MemoryBlock);
                newBlock->Next = current->Next;
                newBlock->Free = 1;

                current->Size = size;
                current->Next = newBlock;
            }
            current->Free = 0;
            return (void*)((uint8*)current + sizeof(MemoryBlock));
        }
        current = current->Next;
    }
    return NULL;
}

void free(void* ptr) {
    if (ptr == NULL) return;

    MemoryBlock* block = (MemoryBlock*)((uint8*)ptr - sizeof(MemoryBlock));
    block->Free = 1;

    if (block->Next != NULL && block->Next->Free) {
        block->Size += sizeof(MemoryBlock) + block->Next->Size;
        block->Next = block->Next->Next;
    }

    MemoryBlock* current = freeList;
    while (current != NULL) {
        if (current->Next == block && current->Free) {
            current->Size += sizeof(MemoryBlock) + block->Size;
            current->Next = block->Next->Next;
            break;
        }
        current = current->Next;
    }
}

extern "C" void* memset(void* s, int c, size_t n) {
    unsigned char* ptr = (unsigned char*)s;
    while (n--) {
        *ptr++ = (unsigned char)c;
    }
    return s;
}

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

uint8 cmosRead(uint8 reg) {
    asm volatile("outb %0, %1" ::"a"(reg), "Nd"(CMOS_ADDRESS));
    asm volatile("jmp 1f; 1: jmp 1f; 1:");
    uint8 value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(CMOS_DATA));
    return value;
};

void* operator new(size_t size) { return malloc(size); }

void* operator new[](size_t size) { return malloc(size); }

void operator delete(void* ptr) noexcept { free(ptr); }

void operator delete[](void* ptr) noexcept { free(ptr); }