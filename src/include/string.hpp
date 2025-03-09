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
    char* data;
    size_t length;

  public:
    String(const char* str = "");
    String(const String& other);
    String(size_t count, char c);
    ~String();

    String& operator=(const String& other);
    String operator+(const String& other) const;
    String operator+(const string& other) const;
    String operator+(char c) const;
    String operator+=(const String& other);
    bool operator==(const String& other) const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    // int Split(char separator, char **result, int MaxSplites);
    bool HasPrefix(const char* prefix);
    bool HasSuffix(const char* suffix);
    String TrimSuffix(const char* suffix);
    String TrimPrefix(const char* prefix);
    // bool HasSuffix(const string* prefix);

    size_t Find(const char* substr) const;
    String Substr(size_t start, size_t len = npos) const;

    const char* c_str() const;
    size_t Len() const;

    static constexpr size_t npos = -1;
};

char* joinStr(const char* str1, const char* str2, char* dest);
int strlen(const char* str);
void strcpy(char* dest, const char* src);
bool strEq(const char* str1, const char* str2);
int SplitStr(char* str, char separator, char** result, int max_splits);
char* strrchr(const char* str, int c);
char* strcat(char* dest, const char* src);
bool HasPrefix(const string* str, const string* prefix);
char* strslice(char* dest, const char* src, size_t n);
char* strncpy(char* dest, const char* src, size_t n);
int splitCmd(const char* str, char** result, int max);
char* replaceStr(const char* src, const char* target, const char* replacement, char* dest);
bool Contains(const char* str, const char* txt);
const char* strstr(const char* haystack, const char* needle);
