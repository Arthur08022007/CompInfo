OFILES = main.o ex3.o
TARGET = ex3
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

ex3.o: ex3.c ex3.h
main.o: main.c ex3.h

