CC = gcc
CFLAGS = -Wall -O2 -Iinclude

OBJ = main.o src/liver.o src/undo.o

all: main

main: $(OBJ)
	$(CC) $(OBJ) -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

src/liver.o: src/liver.c include/liver.h include/list.h
	$(CC) $(CFLAGS) -c src/liver.c -o src/liver.o

src/undo.o: src/undo.c include/undo.h include/list.h
	$(CC) $(CFLAGS) -c src/undo.c -o src/undo.o

clean:
	rm -f main *.o src/*.o
