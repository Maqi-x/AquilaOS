/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once

#include <types.hpp>

void input(char* buffer, uint16 maxLength = 256, bool secret = false, uint8 color = 0x07, bool multiline = false, const char* end = "");
uint8 readYN(char* text, uint8 color);