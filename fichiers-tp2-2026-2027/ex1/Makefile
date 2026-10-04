SRCS = main.c filter.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = filter


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

filter.o: filter.c filter.h
main.o: main.c filter.h
