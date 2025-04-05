CC = gcc
CFLAGS = -Wall -g
TARGET = alloc
SRC_FILES = main.c alloc.c dealloc.c init_alloc.c clean_up.c
OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c alloc.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run