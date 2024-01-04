.PHONY: clean dir


INCLUDE = -Iinclude
CC = gcc
CXX = g++
CFLAGS = -Wfatal-errors -Wall -g $(INCLUDE)
CPP_FLAGS = -std=c++11 -Wfatal-errors -Wall $(INCLUDE)

TEST = test/*.h
OBJ = src/*.c

all: clean fs

test_all: clean test run_test
	
run: fs
	./bin/main

fs: main.c dir $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) main.c -o bin/main


test: clean dir $(OBJ) $(TEST)
	$(CXX) $(CPP_FLAGS) $(OBJ) test/ut_main.cpp -o bin/ut_main -lgtest -lpthread

run_test: test
	./bin/ut_main

dir:
	mkdir -p bin

clean:
	rm -rf bin