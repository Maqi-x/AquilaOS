#include "map.h"

KeyValue map[MAP_SIZE];

uint32_t hash(string key) {
    uint32_t hashValue = 0;
    while (*key) {
        hashValue = (hashValue * 31) + *key++;
    }
    return hashValue % MAP_SIZE;
}

void mapAdd(string key, string value) {
    uint32_t index = hash(key);
    map[index] = KeyValue{key, value};
}

string mapGet(string key) {
    uint32_t index = hash(key);
    return map[index].value;
}

void mapRemove(string key) {
    uint32_t index = hash(key);
    map[index] = KeyValue{nullptr, nullptr};
}

uint32_t getSize() {
    uint32_t count = 0;
    for (uint32_t i = 0; i < MAP_SIZE; i++) {
        if (map[i].key != nullptr) {
            count++;
        }
    }
    return count;
}

string mapKeyAt(string key) {
    uint32_t index = hash(key);
    if (map[index].key != nullptr && map[index].key == key) {
        return map[index].value;
    }
    return nullptr;
}