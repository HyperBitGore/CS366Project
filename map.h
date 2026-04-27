#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024

typedef struct map {
        char* arr;
        int arr_length;
        int width;
        int height;
        int px;
        int py;
        struct map* next;
        struct map* prev;
} map;

typedef map* (*interact_fn)(map*);
typedef unsigned char u8;

map* loadMap(const char* name);
void renderMap(map* m1);

void playerMovement(map* m1, char* input);

void interactSetup();
map* interact(map* m1);

#endif

