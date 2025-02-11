/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once

#include <memory.hpp>
#include <types.hpp>

class String {
  private:
    char *data;
    size_t length;

  public:
    String(const char *str = "");
    String(const String &other);
    ~String();
    String &operator=(const String &other);
    String operator+(const String &other) const;
    String operator+(const string &other) const;
    String operator+=(const String &other);
    bool operator==(const String &other) const;
    // int Split(char separator, char **result, int MaxSplites);
    bool HasPrefix(const char *prefix);
    // bool HasSuffix(const string* prefix);
    const char *c_str() const;
    size_t Len() const;
};

extern char *joinStr(const char *str1, const char *str2, char *dest);
extern int strlen(const char *str);
extern void strcpy(char *dest, const char *src);
extern bool strEq(const char *str1, const char *str2);
extern int SplitStr(char *str, char separator, char **result, int max_splits);
extern char *strrchr(const char *str, int c);
extern char *strcat(char *dest, const char *src);
extern bool HasPrefix(const string *str, const string *prefix);
extern char *strslice(char *dest, const char *src, size_t n);
extern int splitCmd(const char *str, char **result, int max);
extern char *replaceStr(const char *src, const char *target, const char *replacement, char *dest);
extern bool Contains(const char *str, const char *txt);
extern int intToStr(char *buffer, int num);
extern int strToInt(const char *str, bool *success);