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

uint8_t inb(uint16_t port);

uint16_t inw(uint16_t port);

void outb(uint16_t port, uint8_t value);

void outw(uint16_t port, uint16_t data);
