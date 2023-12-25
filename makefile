.PHONY: clean

CC = gcc
CFLAGS = -Wfatal-errors -Wall -g

OBJ = ./src/*.c

all: clean fs
	
fs: main.c SRC
	mkdir -p bin
	$(CC) $(CFLAGS) main.c -o bin/main $(OBJ)

run: fs
	./bin/main

clean:
	rm -rf bin