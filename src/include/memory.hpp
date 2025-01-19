/**
 * -------------------------------------------------------------------------
 *                                   AquilaOS
 * (c) 2022-2024 Interpuce
 * 
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Interpuce/AquilaOS/blob/main/LICENSE.md
 * -------------------------------------------------------------------------
 */

#include <types.hpp>

extern void *memcpy(void *dest, const void *src, size_t n);
extern void *malloc(size_t size);
extern void init_memory();
extern void free(void *ptr);
extern "C" void* memset(void* s, int c, size_t n);
