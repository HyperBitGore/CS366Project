#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int map[] = {
1, 1, 1, 1, 1,
1, 0, 0, 0, 1,
1, 0, 0, 0, 1,
1, 0, 0, 0, 1,
1, 0, 0, 0, 1,
1, 1, 1, 1, 1
};


int main () {
	int run = 0;
	int px = 7;
	char* input = malloc(1024);
	while (run < 150) {
		system("clear");
		int i = 0;
		for (i = 0; i < 30; i++) {
			if (i % 5 == 0) {
				printf("\n");
			}
			if (i == px) {
				printf("@");
			} else {
				switch (map[i]) {
					case 1:
						printf("#");
						break;	
					case 0:
						printf(" ");
						break;
				}
			}
		}	
		printf("\n");
		scanf("%s", input);
		if (strcmp(input, "right") == 0) {
			px += 1;	
		}
		run += 1;
	}
	free(input);
	return 0;
}
