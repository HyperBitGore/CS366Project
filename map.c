#include "map.h"

map* loadMap (const char* file) {
	FILE* fptr;
	/* getting file size */
	long size = -1;
	fptr = fopen(file, "rb");
	if (fptr == NULL) {
		printf("Failed to open file!\n");
		return NULL;
	}
	if (fseek(fptr, 0, SEEK_END) == 0) {
		size = ftell(fptr);
	}
	fclose(fptr);
	if (size == -1) {
		printf("Error processing file size!\n");
		return NULL;
	}
	fptr = fopen(file, "r");
	int width = 0;
	int height = 0;
	int c;
	int count = 0;
	char* arr = malloc(size);
	int i = 0;
	while ((c = fgetc(fptr)) != EOF) {
		if ( c != '\n') {
			arr[i] = c;
			i++;	
			count++;	
		} else {
			if (width < count ) {
				width = count;
			}
			height++;
			count = 0;
		}
		printf("%c", c);
	}
	map* m1 = (map*)malloc(sizeof(map));
	m1->arr = arr;
	m1->arr_length = i;
	m1->width = width;
	m1->height = height;
	m1->next = NULL;
	fclose(fptr);
	return m1;
}
