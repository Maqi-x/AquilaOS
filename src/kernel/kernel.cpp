/**
 * -------------------------------------------------------------------------
 *                                   AquilaOS
 * (c) 2022-2024 Interpuce
 * 
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Interpuce/AquilaOS/blob/main/LICENSE.md
 * -------------------------------------------------------------------------
 */

#include <types.hpp>

extern int TermStart(uint16_t theme);
extern void kernelpanic(const char *errcode);

extern "C" void main() {
    TermStart(0x0B);
    kernelpanic("KERNEL_MAIN_LOOP_EXITED");
}
