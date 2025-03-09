/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#if defined(__GNUC__) && !defined(__clang__)
#    pragma GCC optimize("-O3")
#elif defined(__clang__)
#    pragma clang optimize on
#else
#    warning Using a compiler other than G++ and clang++ can cause AquilaOS compilation problems!
#endif

#include <memory.hpp>
#include <ports.hpp>
#include <types.hpp>

extern void TermStart();
extern void kernelpanic(const char* errcode);

extern void printstr(const char* str, uint8 color);

void (*tasksOnStart[])() = {
    InitMemory,
    TermStart,
};

extern "C" void main() {
    auto tasksLen = sizeof(tasksOnStart) / sizeof(tasksOnStart[0]);
    for (unsigned int i = 0; i < tasksLen; i++) {
        tasksOnStart[i]();
    }

    kernelpanic("KERNEL_MAIN_LOOP_EXITED");
}

constexpr size_t maxAtexitFuncs = 32;
static FuncPtr atexitFuncs[maxAtexitFuncs];
static size_t atexitCount = 0;

extern "C" int atexit(FuncPtr func) {
    if (atexitCount >= maxAtexitFuncs) {
        return -1;
    }
    atexitFuncs[atexitCount++] = func;
    return 0;
}

extern "C" void callAtexit() {
    for (size_t i = 0; i < atexitCount; i++) {
        atexitFuncs[i]();
    }
}

extern "C" void pageFaultHandler() {
    printstr("Page Fault!\n", 0x07);
    while (true);
}
