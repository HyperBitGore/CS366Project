#include <string.h>
#include <stdlib.h>
#include "map.h"



int main () {
	map* m1 = loadMap("map1.txt");
	printf("width: %d, height: %d\n", m1->width, m1->height);
	char* input = malloc(1024);
	int run = 1;
	while (run) {
		system("clear");
		renderMap (m1);	
		scanf("%s", input);
		if (strcmp(input, "right") == 0) {
			m1->px += 1;	
		} else if (strcmp(input, "left") == 0) {
			m1->px -= 1;
		} else if (strcmp(input, "up") == 0) {
			m1->py -= 1;
		} else if (strcmp(input, "down") == 0) {
			m1->py += 1;
		}
	}
	free(input);
	return 0;
}
