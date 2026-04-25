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
			count = 0;
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
	/* if last line doesn't have newline */
	if (count > 0) {
		if (width < count) {
			width = count;
		}
		height++;
	}
	int row = 0;
	count = 0;
	while ((c = fgetc(fptr)) != EOF) {
		if ( c != '\n') {
			switch (c) {
				case '@':
					px = count;
					py = row;
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
			row++;
		}
	}
	if (count > 0) {
		while (count < width) {
			arr[i++] = ' ';
			count++;
		}
	}
	map* m1 = (map*)malloc(sizeof(map));
	m1->arr = arr;
	m1->arr_length = i;
	m1->width = width;
	m1->height = height;
	m1->next = NULL;
	m1->prev = NULL;
	m1->px = px;
	m1->py = py;
	fclose(fptr);
	return m1;
}

void renderMap (map* m1) {
	int x = 0;
	int y = 0;
	printf("px: %d, py: %d\n", m1->px, m1->py);
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
#define CAN_MOVE_LENGTH 3
char can_move[] = {
	' ', '<', '>'
};

int moveable (map* m1, int px, int py) {
	int i;
	for (i = 0; i < CAN_MOVE_LENGTH; i++) {
		if (m1->arr[py * m1->width + px] == can_move[i]) {
			return 1;
		}
	}
	return 0;
}

void playerMovement (map* m1, char* input) {
	if (strcmp(input, "right") == 0) {
		m1->px += 1;	
		if (!moveable(m1, m1->px, m1->py)) {
			m1->px -= 1;
		}	
	} else if (strcmp(input, "left") == 0) {
		m1->px -= 1;
		if (!moveable(m1, m1->px, m1->py)) {
			m1->px += 1;
		}
	} else if (strcmp(input, "up") == 0) {
		m1->py -= 1;
		if (!moveable(m1, m1->px, m1->py)) {
			m1->py += 1;
		}
	} else if (strcmp(input, "down") == 0) {
		m1->py += 1;
		if (!moveable(m1, m1->px, m1->py)) {
			m1->py -= 1;
		}
	}

}
map* empty (map* m1) {
	return m1;	
}
map* nextMap (map* m1) {
	if (m1->next != NULL) {
		map* next = m1->next;
		free(m1);
		return next;
	}
	return m1;
}

interact_fn* interacts = NULL;
void interactSetup () {
	interacts = (interact_fn*)malloc(255 * sizeof(interact_fn));
	u8 i = 0;
	for (; i < 255; i++) {
		interacts[i] = empty;
	}
	interacts['>'] = nextMap;
}
map* interact (map* m1) {
	u8 val = m1->arr[m1->py * m1->width + m1->px];	
	interact_fn interact = interacts[val];
	map* m2 = interact(m1);
	return m2;
}
