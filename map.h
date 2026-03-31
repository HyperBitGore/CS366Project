#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char* arr;
	int arr_length;
	int width;
	int height;
	int px;
	int py;
	struct map* next;
} map;

map* loadMap (const char* name);
