OFILES = main.o ex2.o
TARGET = ex2
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

ex2.o: ex2.c ex2.h
main.o: main.c ex2.h

