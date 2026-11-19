CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

main: main.o BTree.o List.o Dict.o bttraversals.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean run

clean:
	rm -f *.o main

run: main
	./main

main.o: main.c BTree.h List.h bttraversals.h
BTree.o: BTree.c BTree.h
List.o: List.c List.h
Dict.o: Dict.c Dict.h
bttraversals.o: bttraversals.c BTree.h List.h Dict.h bttraversals.h
