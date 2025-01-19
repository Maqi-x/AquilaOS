/**
 * -------------------------------------------------------------------------
 *                                   AquilaOS
 * (c) 2022-2024 Interpuce
 * 
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Interpuce/AquilaOS/blob/main/LICENSE.md
 * -------------------------------------------------------------------------
 */

#include <string.hpp>
#include <types.hpp>
#include <memory.hpp>

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
    while ((*dest++ = *src++) != '\0');
}

int strEq(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1++ != *str2++) {
            return 0;
        }
    }
    return (*str1 == '\0' && *str2 == '\0') ? 1 : 0;
}

int SplitStr(char *str, char separator, char **result, int max_splits) {
    int count = 0;

    while (*str != '\0') {
        if (count >= max_splits) {
            return -1;
        }
        result[count++] = str;

        while (*str != separator && *str != '\0') {
            str++;
        }

        if (*str == separator) {
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

bool HasPerfix(const string *str, const string *prefix) {
    while (*prefix) {
        if (*str++ != *prefix++) {
            return false;
        }
    }
    return true;
}

char* strslice (char *dest, const char *src, size_t n) {
    char *destp = dest;
    
    for (; n != 0 && *src != 0; --n) {
        *destp++ = *src++;
    }

    *destp = 0;

    return dest;
}