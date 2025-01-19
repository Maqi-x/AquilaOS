#include <stdint.h>
#ifndef MAP_H
#define MAP_H

typedef const char* string;

struct KeyValue {
    string key;
    string value;
};

#define MAP_SIZE 256

extern KeyValue map[MAP_SIZE];

uint32_t hash(string key);
void mapAdd(string key, string value);
string mapGet(string key);
void mapRemove(string key);
uint32_t mapSize();
string mapKeyAt(string key);

#endif