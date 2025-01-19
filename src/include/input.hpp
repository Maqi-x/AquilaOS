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

void input(char *buffer, uint16_t max_length, uint8_t secret, uint8_t color);
uint8_t read_yn(char *text, uint8_t color);