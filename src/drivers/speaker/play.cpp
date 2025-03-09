/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <ports.hpp>
#include <screen.hpp>
#include <string.hpp>

#include <time.hpp>

namespace speaker {

#define SPEAKER_PORT 0x61
#define PIT_CONTROL_PORT 0x43
#define PIT_CHANNEL2 0x42

uint8 vfrg(uint32 freq) { return freq >= 20 && freq <= 20000; }

uint8 vdur(uint32 duration) { return duration > 0; }

void speaker(uint32 freq, uint32 duration) {
    if (!vfrg(freq)) {
        return;
    }

    if (!vdur(duration)) {
        return;
    }

    uint16 divisor = 1193180 / freq;

    outb(PIT_CONTROL_PORT, 0xB6);

    outb(PIT_CHANNEL2, (uint8)(divisor & 0xFF));
    outb(PIT_CHANNEL2, (uint8)((divisor >> 8) & 0xFF));

    uint8 tmp = inb(SPEAKER_PORT);
    outb(SPEAKER_PORT, tmp | 3);

    time::Sleep(duration);

    tmp = inb(SPEAKER_PORT);
    outb(SPEAKER_PORT, tmp & ~3);
}

} // namespace speaker