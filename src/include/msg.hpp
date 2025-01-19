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

extern void print_error(const string str);
extern void print_info(const string str);
extern void print_ok(const string str);
extern void print_warn(const string str);
extern void print_custom(const string str, uint8_t color, uint8_t scolor);
extern void print(const string str, uint8_t color);
extern void println(const string str, uint8_t color);
