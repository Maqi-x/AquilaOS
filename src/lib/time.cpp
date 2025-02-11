#include <ports.hpp>

namespace time {

#define PIT_FREQUENCY 1193182 // Hz
#define PIT_CHANNEL0_PORT 0x40
#define PIT_CMD_PORT 0x43

void Sleep(long duration) {
    uint16_t divisor = PIT_FREQUENCY * duration / 1000;

    outb(PIT_CMD_PORT, 0x36); // 0x36 = 00110110b
    outb(PIT_CHANNEL0_PORT, divisor & 0xFF);
    outb(PIT_CHANNEL0_PORT, (divisor >> 8) & 0xFF);

    while ((inb(0x61) & 0x20) == 0);
}

}