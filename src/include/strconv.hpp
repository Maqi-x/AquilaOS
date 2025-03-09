#pragma once
#include <string.hpp>

namespace strconv {

int LongToStr(char* buffer, long num);
long StrToLong(const char* str, bool* success);
String LongToString(long num);
int IntToStr(char* buffer, int num);
int StrToInt(const char* str, bool* success);
String IntToString(int num);

String FloatToString(float64 num, int precision = 0);
int FloatToStr(char* buffer, float64 num, int precision = 0);

} // namespace strconv