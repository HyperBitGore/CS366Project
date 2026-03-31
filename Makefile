CC = gcc
CFLAGS = -ansi -Wall
LDFLAGS = -lm
TARGET = main
SRC = main.c map.h map.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TARGET) $(OBJ)
