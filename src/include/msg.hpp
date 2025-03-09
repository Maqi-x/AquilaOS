/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once

#include <screen.hpp>
#include <strconv.hpp>
#include <string.hpp>
#include <types.hpp>

#include <TypeTraits.hpp>

constexpr uint8 defaultColor = 0x07;

namespace io {

// ---------------- Print ------------------- //
void Print(const string str, uint8 color = defaultColor);
void Print(String str, uint8 color = defaultColor);
void Println(const string str, uint8 color = defaultColor);
void Println(String str, uint8 color = defaultColor);
void Println(int num, uint8 color = defaultColor);
String Prompt(String prompt, uint8 promptClr = defaultColor, uint8 inputClr = defaultColor, bool secret = false);

inline String Sprintf(const String& format) { return format; }

template <typename T, typename... Args> String Sprintf(const String& format, T value, Args... args) {
    size_t pos = format.Find("%");
    if (pos == String::npos || pos == format.Len() - 1) {
        return format;
    }

    char specifier = format[pos + 1];
    String before = format.Substr(0, pos);
    String after = format.Substr(pos + 2);
    String replacement;

    switch (specifier) {
    case 'd':
        if constexpr (IsIntegral<T>::value) {
            replacement = strconv::IntToString((int)value);
        } else {
            replacement = "InvalidInt";
        }
        break;
    case 'f':
        if constexpr (IsFloatingPoint<T>::value) {
            replacement = String(strconv::FloatToString((float64)value));
        } else {
            replacement = "InvalidFloat";
        }
        break;
    case 's':
        if constexpr (IsSame<T, const char*>::value || IsSame<T, char*>::value) {
            replacement = String(value);
        } else if constexpr (IsSame<T, String>::value) {
            replacement = String(value);
        } else {
            replacement = "InvalidStr";
        }
        break;
    case 'c':
        if constexpr (IsSame<T, char>::value) {
            replacement = String(1, value);
        } else {
            replacement = "InvalidChar";
        }
        break;
    case 't':
        if constexpr (IsSame<T, bool>::value) {
            if (value)
                replacement = "true";
            else
                replacement = "false";
        } else {
            replacement = "InvalidBool";
        }
        break;
    default:
        replacement = String("%") + specifier;
    }

    return before + replacement + Sprintf(after, args...);
}

template <typename T, typename... Args> void Printf(const String& format, T value, Args... args) { Print(Sprintf(format, value, args...)); }
template <typename T, typename... Args> void Printlnf(const String& format, T value, Args... args) { Println(Sprintf(format, value, args...)); }

void ShowError(const string str);
void ShowInfo(const string str);
void ShowOk(const string str);
void ShowWarn(const string str);
// void io::ShowCustomMsg(const string str, uint8 color, uint8 scolor);
void ShowSuccess(const string str);

void ShowError(String str);
void ShowInfo(String str);
void ShowOk(String str);
void ShowWarn(String str);
// void io::ShowCustomMsg(const string str, uint8 color, uint8 scolor);
void ShowSuccess(String str);

void ShowErrorf(const String& format);
template <typename T, typename... Args> void ShowErrorf(const String& format, T value, Args... args);

void ShowInfof(const String& format);
template <typename T, typename... Args> void ShowInfof(const String& format, T value, Args... args);

void ShowWarnf(const String& format);
template <typename T, typename... Args> void ShowWarnf(const String& format, T value, Args... args);

void ShowOkf(const String& format);
template <typename T, typename... Args> void ShowOkf(const String& format, T value, Args... args);

void ShowSuccessf(const String& format);
template <typename T, typename... Args> void ShowSuccessf(const String& format, T value, Args... args);

// ------------------ Definitions ------------------- //

inline void ShowErrorf(const String& format) {
    printstr(" [ ERROR ]: ", 0x04);
    Println(Sprintf(format));
}

template <typename T, typename... Args> inline void ShowErrorf(const String& format, T value, Args... args) {
    printstr(" [ ERROR ]: ", 0x04);
    Println(Sprintf(format, value, args...));
}

inline void ShowInfof(const String& format) {
    printstr(" [ INFO ]: ", 0x01);
    Println(Sprintf(format));
}

template <typename T, typename... Args> inline void ShowInfof(const String& format, T value, Args... args) {
    printstr(" [ INFO ]: ", 0x01);
    Println(Sprintf(format, value, args...));
}

inline void ShowWarnf(const String& format) {
    printstr(" [ WARNING ]: ", 0x0E);
    Println(Sprintf(format));
}

template <typename T, typename... Args> inline void ShowWarnf(const String& format, T value, Args... args) {
    printstr(" [ WARNING ]: ", 0x0E);
    Println(Sprintf(format, value, args...));
}

inline void ShowOkf(const String& format) {
    printstr(" [ OK ]: ", 0x0B);
    Println(Sprintf(format));
}

template <typename T, typename... Args> inline void ShowOkf(const String& format, T value, Args... args) {
    printstr(" [ OK ]: ", 0x0B);
    Println(Sprintf(format, value, args...));
}

inline void ShowSuccessf(const String& format) {
    printstr(" [ SUCCESS ]: ", 0x0A);
    Println(Sprintf(format));
}

template <typename T, typename... Args> inline void ShowSuccessf(const String& format, T value, Args... args) {
    printstr(" [ SUCCESS ]: ", 0x0A);
    Println(Sprintf(format, value, args...));
}

} // namespace io