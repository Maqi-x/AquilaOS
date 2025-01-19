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

#define COLOR_1 0x47
#define COLOR_2 0x4F
#define COLOR_3 0x44

#include <msg.hpp>
#include <types.hpp>
#include <screen.hpp>

void kernelpanic(const char *errcode);