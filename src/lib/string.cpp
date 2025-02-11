/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <memory.hpp>
#include <msg.hpp>
#include <string.hpp>
#include <types.hpp>

// ------------------------- UTILS ---------------------------- //
int strToInt(const char *str, bool *success) {
    if (str == nullptr || *str == '\0') {
        *success = false;
        return -1;
    }

    int result = 0, sign = 1;
    int i = 0;

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

int splitCmd(const char *str, char **result, int max) {
    int count = 0;
    bool inQ = false;
    char *temp = const_cast<char *>(str);

    while (*temp != '\0' && count < max) {
        while (*temp == ' ') {
            temp++;
        }

        if (*temp == '\0') {
            break;
        }

        if (*temp == '\"') {
            temp++;
            result[count++] = temp;
            inQ = true;

            while (*temp != '\0' && inQ) {
                if (*temp == '\"') {
                    inQ = false;
                    *temp = '\0';
                } else {
                    temp++;
                }
            }
            temp++;
        } else {
            result[count++] = temp;

            while (*temp != ' ' && *temp != '\0') {
                temp++;
            }
        }

        if (*temp == ' ') {
            *temp = '\0';
            temp++;
        }
    }

    return count;
}

int intToStr(char *buffer, int num) {
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

// --------------------- "LEGACY" STRING -------------------------- //

char *joinStr(const char *str1, const char *str2, char *dest) {
    strcpy(dest, str1);
    strcat(dest, str2);
    return dest;
}

int strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void strcpy(char *dest, const char *src) {
    while ((*dest++ = *src++) != '\0')
        ;
}

bool strEq(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1++ != *str2++) {
            return 0;
        }
    }
    return (*str1 == '\0' && *str2 == '\0');
}

int SplitStr(char *str, char sep, char **result, int max) {
    int count = 0;

    while (*str != '\0') {
        if (count >= max) {
            return -1;
        }
        result[count++] = str;

        while (*str != sep && *str != '\0') {
            str++;
        }

        if (*str == sep) {
            *str = '\0';
            str++;
        }
    }

    return count;
}

char *strrchr(const char *str, int c) {
    char *last = nullptr;
    while (*str) {
        if (*str == (char)c) {
            last = (char *)str;
        }
        str++;
    }
    return last;
}

char *strcat(char *dest, const char *src) {
    char *start = dest;

    while (*dest) {
        dest++;
    }

    while (*src) {
        *dest++ = *src++;
    }

    *dest = '\0';
    return start;
}

bool HasPrefix(const char *str, const char *prefix) {
    // if (!Contains(str, prefix)) return false;
    while (*prefix) {
        if (*str++ != *prefix++) {
            return false;
        }
    }
    return true;
}

bool Contains(const char *str, const char *txt) {
    while (*str) {
        if (strEq(str, txt)) {
            return 1;
        }
        str++;
    }

    return 0;
}

char *strslice(char *dest, const char *src, size_t n) {
    char *destp = dest;

    for (; n != 0 && *src != 0; --n) {
        *destp++ = *src++;
    }

    *destp = 0;

    return dest;
}

char *replaceStr(const char *src, const char *target, const char *replacement, char *dest) {
    char *d = dest;
    const char *s = src;
    size_t targetLen = strlen(target);
    size_t replacementLen = strlen(replacement);

    while (*s) {
        if (strEq(s, target)) {
            strcpy(d, replacement);
            d += replacementLen;
            s += targetLen;
        } else {
            *d++ = *s++;
        }
    }

    *d = '\0';
    return dest;
}

// --------------------------------- NEW STRING -------------------------- //

String::String(const char *str) {
    if (!str) {
        length = 0;
        data = static_cast<char *>(malloc(1));
        if (data) {
            data[0] = '\0';
        }
        return;
    }

    length = strlen(str);
    data = static_cast<char *>(malloc(length + 1));
    if (data) {
        strcpy(data, str);
    }
}

String::String(const String &other) {
    length = other.length;
    data = static_cast<char *>(malloc(length + 1));
    if (data) {
        strcpy(data, other.data);
    }
}

String::~String() { free(data); }

String &String::operator=(const String &other) {
    if (this != &other) {
        free(data);
        length = other.length;
        data = static_cast<char *>(malloc(length + 1));
        if (data) {
            strcpy(data, other.data);
        }
    }
    return *this;
}

String String::operator+(const String &other) const {
    char *newData = static_cast<char *>(malloc(length + other.length + 1));
    if (!newData) return *this;
    joinStr(data, other.data, newData);
    return String(newData);
}

String String::operator+(const string &rawOther) const {
    String other(rawOther);
    char *newData = static_cast<char *>(malloc(length + other.length + 1));
    if (!newData) return *this;
    joinStr(data, other.data, newData);
    return String(newData);
}

String String::operator+=(const String &other) {
    char *newData = static_cast<char *>(malloc(length + other.length + 1));
    if (!newData) return *this;
    joinStr(data, other.data, newData);
    free(data);
    data = newData;
    length += other.length;
    return *this;
}

const char *String::c_str() const { return data; }

bool String::operator==(const String &other) const { return strEq(data, other.data); }

size_t String::Len() const { return length; }

bool String::HasPrefix(const char *prefix) { return ::HasPrefix(data, prefix); }