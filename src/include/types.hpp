/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

// #define useint128

#ifndef NULL
#define NULL ((void*)0)

typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int64;
typedef unsigned long long uint64;

#ifdef useint128
typedef __int128_t int128;
typedef __uint128_t uint128;
#endif

#if 0
maqix was here;
#endif

typedef float float32;
typedef double float64;

typedef unsigned int size_t;

typedef unsigned int uintptr;
typedef signed int intptr;

typedef void (*FuncPtr)();

typedef const char* string;

#endif