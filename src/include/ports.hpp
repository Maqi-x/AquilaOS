/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once

#include <types.hpp>

uint8 inb(uint16 port);

uint16 inw(uint16 port);

void outb(uint16 port, uint8 value);

void outw(uint16 port, uint16 data);
