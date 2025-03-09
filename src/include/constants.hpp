/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <types.hpp>

#pragma once

constexpr string AQUILA_NAME = "AquilaOS Developer Preview";
constexpr string AQUILA_VERSION = "Beta@5";
// constexpr string PC_NAME = "AquilaPC";
constexpr string PC_ARCH = "x86";

#if defined(__clang__)
constexpr string COMPILER = "Clang";
#elif defined(__GNUC__) || defined(__GNUG__)
constexpr string COMPILER = "GCC";
#elif defined(_MSC_VER)
constexpr string COMPILER = "MSVC";
#else
constexpr string COMPILER = "Unknown";
#endif