#include "map.h"

map* loadMap(const char* file) {
        FILE* fptr;
        char line[INPUT_SIZE];
        char nextFile[INPUT_SIZE];
        int width;
        int height;
        int len;
        int row;
        int col;
        int i;
        int px;
        int py;
        char* arr;
        map* m1;

        width = 0;
        height = 0;
        nextFile[0] = '\0';

        fptr = fopen(file, "r");
        if (fptr == NULL) {
                printf("Failed to open file: %s\n", file);
                return NULL;
        }

        while (fgets(line, INPUT_SIZE, fptr) != NULL) {
                len = strlen(line);

                if (len > 0 && line[len - 1] == '\n') {
                        line[len - 1] = '\0';
                        len--;
                }

                if (strcmp(line, "EOF") == 0) {
                        break;
                }

                if (width < len) {
                        width = len;
                }

                height++;
        }

        while (fgets(line, INPUT_SIZE, fptr) != NULL) {
                if (strncmp(line, "next=", 5) == 0) {
                        strcpy(nextFile, line + 5);

                        len = strlen(nextFile);
                        if (len > 0 && nextFile[len - 1] == '\n') {
                                nextFile[len - 1] = '\0';
                        }
                }
        }

        fclose(fptr);

        arr = malloc(width * height);
        if (arr == NULL) {
                printf("Failed to allocate map memory.\n");
                return NULL;
        }

        for (i = 0; i < width * height; i++) {
                arr[i] = ' ';
        }

        fptr = fopen(file, "r");
        if (fptr == NULL) {
                printf("Failed to open file: %s\n", file);
                free(arr);
                return NULL;
        }

        row = 0;
        px = 0;
        py = 0;

        while (fgets(line, INPUT_SIZE, fptr) != NULL && row < height) {
                len = strlen(line);

                if (len > 0 && line[len - 1] == '\n') {
                        line[len - 1] = '\0';
                        len--;
                }

                if (strcmp(line, "EOF") == 0) {
                        break;
                }

                for (col = 0; col < len; col++) {
                        if (line[col] == '@') {
                                px = col;
                                py = row;
                                arr[row * width + col] = ' ';
                        } else {
                                arr[row * width + col] = line[col];
                        }
                }

                row++;
        }

        fclose(fptr);

        m1 = malloc(sizeof(map));
        if (m1 == NULL) {
                printf("Failed to allocate map struct.\n");
                free(arr);
                return NULL;
        }

        m1->arr = arr;
        m1->arr_length = width * height;
        m1->width = width;
        m1->height = height;
        m1->px = px;
        m1->py = py;
        m1->next = NULL;
        m1->prev = NULL;

        if (nextFile[0] != '\0') {
                m1->next = loadMap(nextFile);

                if (m1->next != NULL) {
                        m1->next->prev = m1;
                }
        }

        return m1;

}
void renderMap(map* m1) {
        int x;
        int y;

        for (y = 0; y < m1->height; y++) {
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

#define CAN_MOVE_LENGTH 8

char can_move[] = {
        ' ', '<', '>', 'T', 'W', 'A', 'E', 'B'
};

int moveable(map* m1, int px, int py) {
        int i;
        char tile;

        if (px < 0 || py < 0 || px >= m1->width || py >= m1->height) {
                return 0;
        }

        tile = m1->arr[py * m1->width + px];

        for (i = 0; i < CAN_MOVE_LENGTH; i++) {
                if (tile == can_move[i]) {
                        return 1;
                }
        }

        return 0;
}

void playerMovement(map* m1, char* input) {
        int nextX;
        int nextY;

        nextX = m1->px;
        nextY = m1->py;

        if (strcmp(input, "right") == 0) {
                nextX++;
        } else if (strcmp(input, "left") == 0) {
                nextX--;
        } else if (strcmp(input, "up") == 0) {
                nextY--;
        } else if (strcmp(input, "down") == 0) {
                nextY++;
        }

        if (moveable(m1, nextX, nextY)) {
                m1->px = nextX;
                m1->py = nextY;
        }
}

map* empty(map* m1) {
        return m1;
}

map* nextMap(map* m1) {
        if (m1->next != NULL) {
                return m1->next;
        }

        return m1;
}

map* prevMap(map* m1) {
        if (m1->prev != NULL) {
                return m1->prev;
        }

        return m1;
}

interact_fn* interacts = NULL;

void interactSetup() {
        u8 i;

        interacts = malloc(255 * sizeof(interact_fn));

        for (i = 0; i < 255; i++) {
                interacts[i] = empty;
        }

        interacts['>'] = nextMap;
        interacts['<'] = prevMap;
}

map* interact(map* m1) {
        u8 val;

        if (interacts == NULL) {
                interactSetup();
        }

        val = m1->arr[m1->py * m1->width + m1->px];

        return interacts[val](m1);
}
