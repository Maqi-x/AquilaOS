/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <types.hpp>

extern "C" void *memcpy(void *dest, const void *src, size_t n);
extern void *malloc(size_t size);
extern void InitMemory();
extern void free(void *ptr);
extern "C" void *memset(void *s, int c, size_t n);