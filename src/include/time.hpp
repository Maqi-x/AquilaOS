/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <string.hpp>

namespace time {
class DateTime {
  public:
    uint8 second, minute, hour, day, month;
    uint16 year;

    void Format(char* buffer) const;
    uint64 ToUnixNano() const;
    uint64 ToUnix() const;

    static DateTime FromUnix(uint64 unixtime);
};

DateTime Now();
void Sleep(uint64 duration);
} // namespace time