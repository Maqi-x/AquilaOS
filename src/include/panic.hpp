/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once

#include <msg.hpp>
#include <screen.hpp>
#include <types.hpp>

constexpr uint8_t COLOR_1 = 0x47;
constexpr uint8_t COLOR_2 = 0x4F;
constexpr uint8_t COLOR_3 = 0x47;

void kernelpanic(const char *errcode);