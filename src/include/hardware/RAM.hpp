#include <string.hpp>
#include <types.hpp>

struct MultibootInfo {
    uint32 flags;
    uint32 memLower;
    uint32 memUpper;
    uint32 mmapLength;
    uint32 mmapAddr;
} __attribute__((packed));

extern uint32 getRAM(MultibootInfo* mboot_ptr);
extern String formatBytes(uint64 bytes);