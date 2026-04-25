#include <stdlib.h>
#include "map.h"



int main () {
	map* m1 = loadMap("map1.txt");
	printf("width: %d, height: %d\n", m1->width, m1->height);
	char* input = malloc(1024);
	interactSetup();
	int run = 1;
	while (run) {
		system("clear");
		renderMap (m1);	
		scanf("%s", input);
		playerMovement(m1, input);	
		if (strcmp(input, "interact") == 0){
			m1 = interact(m1);
		}	
	}
	free(input);
	return 0;
}
