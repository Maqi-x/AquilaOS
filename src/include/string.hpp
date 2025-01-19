/**
 * -------------------------------------------------------------------------
 *                                   AquilaOS
 * (c) 2022-2024 Interpuce
 * 
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Interpuce/AquilaOS/blob/main/LICENSE.md
 * -------------------------------------------------------------------------
 */

#pragma once

#include <types.hpp>

extern int strlen(const char *str);
extern void strcpy(char *dest, const char *src);
extern int strEq(const char *str1, const char *str2);
extern int SplitStr(char *str, char separator, char **result, int max_splits);
extern char *strrchr(const char *str, int c);
extern char *strcat(char *dest, const char *src);
extern bool HasPerfix(const string *str, const string *prefix);
extern char* strslice(char *dest, const char *src, size_t n);