SRCS = hanoi.c stack-int-ll.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = hanoi


CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG) 3
runwin: $(PROG)
	$(PROG).exe 3

hanoi.o: hanoi.c stack-int.h
stack-int-ll.o: stack-int-ll.c stack-int.h
