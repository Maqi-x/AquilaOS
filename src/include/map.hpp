#pragma once

#include <memory.hpp>
#include <string.hpp>

namespace map {
extern "C" {
typedef struct {
    char *key;
    char *value;
} Pair;

typedef struct {
    Pair *data;
    size_t capacity;
    size_t size;
} MapStrStr;

void Init(MapStrStr *map, size_t initialCapacity);
void Free(MapStrStr *map);
void Resize(MapStrStr *map);
void Insert(MapStrStr *map, const char *key, const char *value);
char *Get(MapStrStr *map, const char *key);
void Remove(MapStrStr *map, const char *key);
}
} // namespace map