/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once

#include <types.hpp>

extern uint16 cursorPos;
void printchar(char c, uint8 color, bool shiftRight = false);
void printstr(const char* str, uint8 color);
void delchar();
void clearscreen();
void paintscreen(uint8 color);
void printint(uint16 value, uint8 color);
void clearline(uint16 line);
void paintline(uint16 line, uint8 color);
void printct(const char* str, uint8 color);

void updateCursor();
