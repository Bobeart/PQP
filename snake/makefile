# compiler flags
#	-g		adds debugging information to the executable file
#	-Wall	turns on most, but not all, compiler warnings
CC = gcc
CFLAGS = -std=c99

Snake: snake.o
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

snake.o: snake.c macros.h

clean:
	$(RM) Snake snake.o