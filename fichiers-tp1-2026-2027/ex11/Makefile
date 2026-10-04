SRCS = intervals.c main.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = intervals

CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

main.o: intervals.h

intervals.o: intervals.h

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG)

runwin: $(PROG)
	$(PROG).exe
