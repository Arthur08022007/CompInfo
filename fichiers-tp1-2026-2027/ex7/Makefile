OFILES = main.o kendalltau.o
TARGET = kendalltau
CC = gcc
CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99

all: $(TARGET)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: all clean run

clean:
	rm -f $(OFILES) $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OFILES)
	$(CC) $(OFILES) -o $(TARGET)

ex7.o: kendalltau.c kendalltau.h
main.o: main.c kendalltau.h

