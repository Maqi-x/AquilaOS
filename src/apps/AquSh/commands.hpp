/*********************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once

#include <screen.hpp>
#include <stdint.h>
#include <string.hpp>
#include <types.hpp>

void cowsay(String message);
void mapf();
void help(uint16_t theme);
extern int AquilNoteMain(uint8_t color, uint8_t barcolor);