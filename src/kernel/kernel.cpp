/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <memory.hpp>
#include <types.hpp>

extern int TermStart(uint16_t theme);
extern void kernelpanic(const char *errcode);

extern "C" void main() {
    InitMemory();
    TermStart(0x0B);
    kernelpanic("KERNEL_MAIN_LOOP_EXITED");
}

typedef void (*FuncPtr)(void);

constexpr size_t maxAtexitFuncs = 32;
static FuncPtr atexitFuncs[maxAtexitFuncs];
static size_t atexitCount = 0;

extern "C" int atexit(void (*func)(void)) {
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
