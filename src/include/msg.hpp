/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once

#include <string.hpp>
#include <types.hpp>

constexpr uint8 defaultColor = 0x07;

namespace io {

// ---------------- Print ------------------- //
extern void Print(const string str, uint8 color = defaultColor);
extern void Print(String str, uint8 color = defaultColor);
extern void Println(const string str, uint8 color = defaultColor);
extern void Println(String str, uint8 color = defaultColor);

extern void ShowError(const string str);
extern void ShowInfo(const string str);
extern void ShowOk(const string str);
extern void ShowWarn(const string str);
// extern void io::ShowCustomMsg(const string str, uint8 color, uint8 scolor);
extern void ShowSuccess(const string str);

extern void ShowError(String str);
extern void ShowInfo(String str);
extern void ShowOk(String str);
extern void ShowWarn(String str);
// extern void io::ShowCustomMsg(const string str, uint8 color, uint8 scolor);
extern void ShowSuccess(String str);

} // namespace io