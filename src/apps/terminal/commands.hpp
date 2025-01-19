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
#include <screen.hpp>
#include <string.hpp>
#include <stdint.h>

void cowsay(char message[1024]);
void map();
void help(uint16_t theme);
extern int AquilNoteMain(uint8_t color, uint8_t barcolor);