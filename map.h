#include <stdio.h>

typedef struct {
	char* arr;
	struct map* next;
} map;

map* loadMap (const char* name);
