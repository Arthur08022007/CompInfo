SRCS = main.c set-hash.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = ex8


CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG)
runwin: $(PROG)
	$(PROG).exe

main.o: main.c set.h
set-hash.o: set-hash.c set.h
