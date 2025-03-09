/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include "map.hpp"
#include <memory.hpp>
#include <msg.hpp>
#include <screen.hpp>

namespace map {

void Init(MapStrStr* map, size_t initialCapacity) {
    map->capacity = initialCapacity;
    map->size = 0;
    map->data = (Pair*)malloc(initialCapacity * sizeof(Pair));
}

void Free(MapStrStr* map) {
    for (size_t i = 0; i < map->size; ++i) {
        free(map->data[i].key);
        free(map->data[i].value);
    }
    free(map->data);
}

void Resize(MapStrStr* map) {
    size_t newCapacity = map->capacity * 2;
    io::Print("Resizing from ", 0x07);
    printint(map->capacity, 0x07);
    io::Print(" to ", 0x07);
    printint(newCapacity, 0x07);
    io::Println("", 0x07);

    Pair* newData = (Pair*)malloc(newCapacity * sizeof(Pair));
    if (!newData) return;

    for (size_t i = 0; i < map->size; ++i) {
        io::Println(map->data[i].key, 0x07);
        newData[i] = map->data[i];
    }

    free(map->data);
    map->data = newData;
    map->capacity = newCapacity;
}

void Insert(MapStrStr* map, const char* key, const char* value) {
    if (map->size == map->capacity) {
        Resize(map);
    }

    for (size_t i = 0; i < map->size; ++i) {
        if (strEq(map->data[i].key, key)) {
            free(map->data[i].value);
            map->data[i].value = (char*)malloc(strlen(value) + 1);
            strcpy(map->data[i].value, value);
            return;
        }
    }

    if (map->size == map->capacity) {
        Resize(map);
    }

    map->data[map->size].key = (char*)malloc(strlen(key) + 1);
    strcpy(map->data[map->size].key, key);

    map->data[map->size].value = (char*)malloc(strlen(value) + 1);
    strcpy(map->data[map->size].value, value);

    ++map->size;
    ;
}

char* Get(MapStrStr* map, const char* key) {
    for (size_t i = 0; i < map->size; ++i) {
        if (strEq(map->data[i].key, key)) {
            return map->data[i].value;
        }
    }
    return nullptr;
}

void Remove(MapStrStr* map, const char* key) {
    for (size_t i = 0; i < map->size; ++i) {
        if (strEq(map->data[i].key, key)) {
            free(map->data[i].key);
            free(map->data[i].value);
            for (size_t j = i; j < map->size - 1; ++j) {
                map->data[j] = map->data[j + 1];
            }
            --map->size;
            return;
        }
    }
}

} // namespace map