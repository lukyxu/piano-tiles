CC = gcc

CFLAGS = -std=c99 -Wall -g -pedantic

LIBS = -lSDL2 -lSDL2_test -lSDL2_ttf -lSDL2_mixer

.SUFFIXES: .c .o .h

.PHONY: all clean

all: executable

game.o: game.h

stack.o: stack.h

utilities.o: utilities.h

menus.o: menus.h

executable: game.o main.o stack.o utilities.o menus.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f *.o
	rm -f executable