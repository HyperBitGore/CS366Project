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
	int width = 0;
	int height = 0;
	int c;
	int count = 0;
	while ((c = fgetc(fptr)) != EOF) {
		if (c != '\n') {
			count++;
		} else {
			if (width < count) {
				width = count;
			}
			height++;
		}
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
	char* arr = malloc(width * height);
	int i = 0;
	int px = 0;
	int py = 0;
	while ((c = fgetc(fptr)) != EOF) {
		if ( c != '\n') {
			switch (c) {
				case '@':
					px = count;
					py = height;
					arr[i] = ' ';
					break;
				default:
					arr[i] = c;
			}
			i++;	
			count++;	
		} else {
			if ( count < width ) {
				int j = count;
				for (; j < width; j++, i++) {
					arr[i] = ' ';
				}
			}	
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
	m1->px = px;
	m1->py = py;
	fclose(fptr);
	return m1;
}

void renderMap (map* m1) {
	int x = 0;
	int y = 0;
	for (; y < m1->height; y++) {
		for (x = 0; x < m1->width; x++) {
			if (x == m1->px && y == m1->py) {
				printf("@");
			} else {
				printf("%c", m1->arr[y * m1->width + x]);
			}
		}
		printf("\n");
	}

}
