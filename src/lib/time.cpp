/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <memory.hpp>
#include <ports.hpp>
#include <time.hpp>

namespace time {

// duration in miliseconds
void Sleep(uint64 duration) {
    const uint32 total = static_cast<uint32>(duration) * 1193UL;
    auto remaining = total;

    asm volatile("cli");

    while (remaining > 0) {
        uint16 chunk = (remaining > 65535) ? 65535 : static_cast<uint16>(remaining);
        remaining -= chunk;

        outb(0x43, 0x38);
        outb(0x40, chunk & 0xFF);
        outb(0x40, chunk >> 8);

        while (true) {
            outb(0x43, 0x00);
            uint16 count = inb(0x40);
            count |= inb(0x40) << 8;
            if (count == 0) break;
        }
    }
}

DateTime Now() {
    DateTime dt;

    while (cmosRead(0x0A) & 0x80);

    uint8 reg_b = cmosRead(0x0B);
    bool isBcd = !(reg_b & 0x04);

    dt.second = cmosRead(0x00);
    dt.minute = cmosRead(0x02);
    dt.hour = cmosRead(0x04);
    dt.day = cmosRead(0x07);
    dt.month = cmosRead(0x08);
    uint8 year = cmosRead(0x09);
    uint8 century = 20;

    auto bcdToBin = [](uint8 val) { return (val >> 4) * 10 + (val & 0x0F); };
    if (isBcd) {
        dt.second = bcdToBin(dt.second);
        dt.minute = bcdToBin(dt.minute);
        dt.hour = bcdToBin(dt.hour);
        dt.day = bcdToBin(dt.day);
        dt.month = bcdToBin(dt.month);
        year = bcdToBin(year);
        century = bcdToBin(cmosRead(0x32));
    }
    dt.year = century * 100 + year;

    if (!(reg_b & 0x02) && (dt.hour & 0x80)) {
        dt.hour = (dt.hour & 0x7F) + 12;
        if (dt.hour == 24) dt.hour = 12;
    } else if (!(reg_b & 0x02)) {
        if (dt.hour == 12) dt.hour = 0;
    }

    return dt;
}

void DateTime::Format(char* buffer) const {
    // ---------- Day ----------- //
    buffer[0] = (day / 10) + '0';
    buffer[1] = (day % 10) + '0';
    buffer[2] = '/';

    // ---------- Month --------- //
    buffer[3] = (month / 10) + '0';
    buffer[4] = (month % 10) + '0';
    buffer[5] = '/';

    // ---------- Year ---------- //
    buffer[6] = (year / 1000) + '0';
    buffer[7] = ((year / 100) % 10) + '0';
    buffer[8] = ((year / 10) % 10) + '0';
    buffer[9] = (year % 10) + '0';
    buffer[10] = ' ';

    // ---------- Hour ---------- //
    buffer[11] = (hour / 10) + '0';
    buffer[12] = (hour % 10) + '0';
    buffer[13] = ':';

    // --------- Minute ---------- //
    buffer[14] = (minute / 10) + '0';
    buffer[15] = (minute % 10) + '0';

    // --------------------------- //

    buffer[16] = '\0';
}

bool isLeapYear(uint16 year) { return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); }

constexpr int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

uint64 DateTime::ToUnix() const {
    uint64 totalDays = 0;
    for (int y = 1970; y < year; y++) {
        totalDays += isLeapYear(y) ? 366 : 365;
    }

    for (int m = 0; m < month - 1; m++) {
        totalDays += daysInMonth[m];
        if (m == 1 && isLeapYear(year)) {
            totalDays += 1;
        }
    }

    totalDays += day - 1;

    uint64 totalSeconds = totalDays * 86400ULL;
    totalSeconds += hour * 3600ULL;
    totalSeconds += minute * 60ULL;
    totalSeconds += second;

    return totalSeconds;
}

uint64 DateTime::ToUnixNano() const {
    uint64 totalDays = 0;
    for (int y = 1970; y < year; y++) {
        totalDays += isLeapYear(y) ? 366 : 365;
    }

    for (int m = 0; m < month - 1; m++) {
        totalDays += daysInMonth[m];
        if (m == 1 && isLeapYear(year)) {
            totalDays += 1;
        }
    }

    totalDays += day - 1;

    uint64 totalSeconds = totalDays * 86400ULL;
    totalSeconds += hour * 3600ULL;
    totalSeconds += minute * 60ULL;
    totalSeconds += second;

    return totalSeconds * 1000000000ULL;
}

DateTime DateTime::FromUnix(uint64 unixtime) {
    DateTime dt;

    uint64 totalSeconds = unixtime;
    dt.second = totalSeconds % 60;
    totalSeconds /= 60;
    dt.minute = totalSeconds % 60;
    totalSeconds /= 60;
    dt.hour = totalSeconds % 24;
    totalSeconds /= 24;

    int year = 1970;
    while (true) {
        uint64 daysInYear = isLeapYear(year) ? 366 : 365;
        if (totalSeconds >= daysInYear) {
            totalSeconds -= daysInYear;
            year++;
        } else {
            break;
        }
    }
    dt.year = year;

    int m = 0;
    while (true) {
        int daysInCurrentMonth = daysInMonth[m];
        if (m == 1 && isLeapYear(year)) {
            daysInCurrentMonth++;
        }
        if (totalSeconds >= daysInCurrentMonth) {
            totalSeconds -= daysInCurrentMonth;
            m++;
        } else {
            break;
        }
    }
    dt.month = m + 1;
    dt.day = totalSeconds + 1;

    return dt;
}

} // namespace time