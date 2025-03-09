#include <hardware/cpu.hpp>
#include <memory.hpp>
#include <stdint.h>

void cpuid(uint32 eax, uint32 ecx, uint32* regs) { asm volatile("cpuid" : "=a"(regs[0]), "=b"(regs[1]), "=c"(regs[2]), "=d"(regs[3]) : "a"(eax), "c"(ecx)); }

char* getCPUName() {
    static char cpuName[49];
    uint32 regs[4];

    cpuid(0x80000002, 0, regs);
    memcpy(cpuName, regs, sizeof(regs));

    cpuid(0x80000003, 0, regs);
    memcpy(cpuName + 16, regs, sizeof(regs));

    cpuid(0x80000004, 0, regs);
    memcpy(cpuName + 32, regs, sizeof(regs));

    cpuName[48] = '\0';
    return cpuName;
}
