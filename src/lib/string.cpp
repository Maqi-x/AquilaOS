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

int splitCmd(const char* str, char** result, int max) {
    int count = 0;
    bool inQ = false;
    char* temp = const_cast<char*>(str);

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

// --------------------- "LEGACY" STRING -------------------------- //

char* joinStr(const char* str1, const char* str2, char* dest) {
    strcpy(dest, str1);
    strcat(dest, str2);
    return dest;
}

int strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void strcpy(char* dest, const char* src) { while ((*dest++ = *src++) != '\0'); }

bool strEq(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1++ != *str2++) {
            return 0;
        }
    }
    return (*str1 == '\0' && *str2 == '\0');
}

int SplitStr(char* str, char sep, char** result, int max) {
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

char* strrchr(const char* str, int c) {
    char* last = nullptr;
    while (*str) {
        if (*str == (char)c) {
            last = (char*)str;
        }
        str++;
    }
    return last;
}

char* strcat(char* dest, const char* src) {
    char* start = dest;

    while (*dest) {
        dest++;
    }

    while (*src) {
        *dest++ = *src++;
    }

    *dest = '\0';
    return start;
}

bool HasPrefix(const char* str, const char* prefix) {
    // if (!Contains(str, prefix)) return false;
    while (*prefix) {
        if (*str++ != *prefix++) {
            return false;
        }
    }
    return true;
}

bool HasSuffix(const char* str, const char* suffix) {
    int strLen = strlen(str), suffixLen = strlen(suffix);

    if (suffixLen > strLen) return false;

    return strEq(str + (strLen - suffixLen), suffix);
}

bool Contains(const char* str, const char* txt) {
    while (*str) {
        if (strEq(str, txt)) {
            return 1;
        }
        str++;
    }

    return 0;
}

char* strslice(char* dest, const char* src, size_t n) {
    char* destp = dest;

    for (; n != 0 && *src != 0; --n) {
        *destp++ = *src++;
    }

    *destp = 0;

    return dest;
}

char* replaceStr(const char* src, const char* target, const char* replacement, char* dest) {
    char* d = dest;
    const char* s = src;
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

char* strncpy(char* dest, const char* src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

const char* strstr(const char* haystack, const char* needle) {
    if (!*needle) {
        return haystack;
    }

    for (; *haystack; haystack++) {
        if (*haystack == *needle) {
            const char* h = haystack;
            const char* n = needle;
            while (*h && *n && *h == *n) {
                h++;
                n++;
            }
            if (!*n) {
                return haystack;
            }
        }
    }
    return nullptr;
}

// --------------------------------- NEW STRING -------------------------- //

String::String(const char* str) {
    if (!str) {
        length = 0;
        data = static_cast<char*>(malloc(1));
        if (data) {
            data[0] = '\0';
        }
        return;
    }

    length = strlen(str);
    data = static_cast<char*>(malloc(length + 1));
    if (data) {
        strcpy(data, str);
    }
}

String::String(const String& other) {
    length = other.length;
    data = static_cast<char*>(malloc(length + 1));
    if (data) {
        strcpy(data, other.data);
    }
}

String::String(size_t count, char c) {
    data = new char[count + 1];
    memset(data, c, count);
    data[count] = '\0';
    length = count;
}

String String::operator+(char c) const {
    size_t newLength = length + 1;
    char* newData = new char[newLength + 1];
    strcpy(newData, data);
    newData[length] = c;
    newData[newLength] = '\0';

    String result(newData);
    delete[] newData;
    return result;
}

String::~String() { free(data); }

String& String::operator=(const String& other) {
    if (this != &other) {
        free(data);
        length = other.length;
        data = static_cast<char*>(malloc(length + 1));
        if (data) {
            strcpy(data, other.data);
        }
    }
    return *this;
}

String String::operator+(const String& other) const {
    char* newData = static_cast<char*>(malloc(length + other.length + 1));
    if (!newData) return *this;
    joinStr(data, other.data, newData);
    return String(newData);
}

String String::operator+(const string& rawOther) const {
    String other(rawOther);
    char* newData = static_cast<char*>(malloc(length + other.length + 1));
    if (!newData) return *this;
    joinStr(data, other.data, newData);
    return String(newData);
}

String String::operator+=(const String& other) {
    char* newData = static_cast<char*>(malloc(length + other.length + 1));
    if (!newData) return *this;
    joinStr(data, other.data, newData);
    free(data);
    data = newData;
    length += other.length;
    return *this;
}

const char* String::c_str() const { return data; }

bool String::operator==(const String& other) const { return strEq(data, other.data); }

size_t String::Len() const { return length; }

bool String::HasPrefix(const char* prefix) { return ::HasPrefix(data, prefix); }
bool String::HasSuffix(const char* suffix) { return ::HasSuffix(data, suffix); }

String String::TrimPrefix(const char* prefix) {
    if (HasPrefix(prefix)) {
        size_t prefixLen = strlen(prefix);
        char* newData = static_cast<char*>(malloc(length - prefixLen + 1));
        if (!newData) return *this;
        strcpy(newData, data + prefixLen);
        String result(newData);
        free(newData);
        return result;
    }
    return *this;
}

String String::TrimSuffix(const char* suffix) {
    if (HasSuffix(suffix)) {
        size_t suffixLen = strlen(suffix);
        char* newData = static_cast<char*>(malloc(length - suffixLen + 1));
        if (!newData) return *this;
        strncpy(newData, data, length - suffixLen);
        newData[length - suffixLen] = '\0';
        String result(newData);
        free(newData);
        return result;
    }
    return *this;
}

size_t String::Find(const char* substr) const {
    const char* pos = strstr(data, substr);
    if (pos) {
        return pos - data;
    }
    return -1;
}

String String::Substr(size_t start, size_t len) const {
    if (len == npos) len = length - start;

    if (start >= length) {
        return String("");
    }

    if (start + len > length) {
        len = length - start;
    }

    char* newData = static_cast<char*>(malloc(len + 1));
    if (!newData) return String("");

    strncpy(newData, data + start, len);
    newData[len] = '\0';

    String result(newData);
    free(newData);
    return result;
}

char& String::operator[](size_t index) { return data[index]; }

const char& String::operator[](size_t index) const { return data[index]; }