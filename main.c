#include <string.h>
#include <stdlib.h>
#include "map.h"



int main () {
	int px = 7;
	map* m1 = loadMap("map1.txt");
	printf("width: %d, height: %d\n", m1->width, m1->height);
	char* input = malloc(1024);
	int run = 1;
	while (run) {
		system("clear");
		int i = 0;
		for (i = 0; i < m1->arr_length; i++) {
			if (i % m1->width == 0 && i != 0) {
				printf("\n");
			} else {
				printf("%c", m1->arr[i]);
			}	
		}
		scanf("%s", input);
		if (strcmp(input, "right") == 0) {
			px += 1;	
		}
	}
	free(input);
	return 0;
}
