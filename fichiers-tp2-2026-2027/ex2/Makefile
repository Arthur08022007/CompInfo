SRCS = main.c findfirsttrue.c image.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = findfirsttrue

CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG) binarized_airplane.pgm

run: $(PROG)
	./$(PROG)

findfirsttrue.o: findfirsttrue.c findfirsttrue.h
image.o: image.c image.h
main.o: main.c findfirsttrue.h image.h
