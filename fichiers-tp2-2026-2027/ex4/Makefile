SRCS = main.c test_searchpattern.c bon_1.c bon_2.c faux_1.c faux_2.c faux_3.c faux_4.c faux_5.c faux_6.c faux_7.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = test_pattern


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
