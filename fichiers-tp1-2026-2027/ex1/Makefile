SRCS1 = main.c maxsum.c
OBJS1 = $(SRCS1:%.c=%.o)
SRCS2 = testTimingMaxSum.c maxsum.c
OBJS2 = $(SRCS2:%.c=%.o)
CC = gcc
PROG1 = maxsum
PROG2 = testtiming

CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG1) $(PROG2)

$(PROG1): $(OBJS1)
	$(CC) -o $@ $(OBJS1) $(LDFLAGS)

$(PROG2): $(OBJS2)
	$(CC) -o $@ $(OBJS2) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS1) $(PROG1)  $(OBJS2) $(PROG2)

run: $(PROG1)
	./$(PROG1)
runtime: $(PROG2)
	./$(PROG2)

runwin: $(PROG1)
	$(PROG1).exe

runwin2: $(PROG2)
	$(PROG2).exe
