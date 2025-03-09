/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <ports.hpp>

uint8 inb(uint16 port) {
    uint8 result;
    asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

uint16 inw(uint16 port) {
    uint16 result;
    asm volatile("inw %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void outb(uint16 port, uint8 value) { asm volatile("outb %0, %1" : : "a"(value), "Nd"(port)); }

void outw(uint16 port, uint16 data) { asm volatile("outw %0, %1" : : "a"(data), "Nd"(port)); }
