#include <strconv.hpp>
#include <string.hpp>

namespace strconv {

long StrToLong(const char* str, bool* success) {
    if (str == nullptr || *str == '\0') {
        *success = false;
        return -1;
    }

    long result = 0, sign = 1;
    long i = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            *success = false;
            return -1;
        }
        i++;
    }

    *success = true;
    return result * sign;
}

int LongToStr(char* buffer, long num) {
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 1;
    }

    char tmp[20];
    int index = 0;

    while (num > 0) {
        tmp[index++] = (num % 10) + '0';
        num /= 10;
    }

    int len = index;
    for (int i = 0; i < len; i++) {
        buffer[i] = tmp[len - i - 1];
    }

    buffer[len] = '\0';

    return len;
}

String LongToString(long num) {
    char buffer[21];
    LongToStr(buffer, num);
    return String(buffer);
}

int StrToInt(const char* str, bool* success) { return (int)StrToLong(str, success); }

int IntToStr(char* buffer, int num) { return LongToStr(buffer, (long)num); }

String IntToString(int num) {
    char buffer[21];
    IntToStr(buffer, num);
    return String(buffer);
}

int FloatToStr(char* buffer, float64 num, int precision) {
    if (buffer == nullptr) {
        return -1;
    }

    long integerPart = (long)num;
    double fractionalPart = num - (double)integerPart;

    int intLen = LongToStr(buffer, integerPart);
    buffer[intLen] = '.';
    intLen++;

    for (int i = 0; i < precision; i++) {
        fractionalPart *= 10;
        int digit = (int)fractionalPart;
        buffer[intLen + i] = '0' + digit;
        fractionalPart -= digit;
    }

    buffer[intLen + 6] = '\0';
    return intLen + 6;
}

String FloatToString(float64 num, int precision) {
    char buffer[35];
    FloatToStr(buffer, num, precision);
    return String(buffer);
}

} // namespace strconv