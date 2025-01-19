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

void printchar(char c, uint8_t color);
void printstr(const char *str, uint8_t color);
void delchar();
void clearscreen();
void paintscreen(uint8_t color);
void printint(uint16_t value, uint8_t color);
void clearline(uint16_t line);
void paintline(uint16_t line, uint8_t color);
void printct(const char *str, uint8_t color);
