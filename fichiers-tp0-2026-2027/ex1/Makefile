OFILES = main.o ex1.o
TARGET = ex1
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

ex1.o: ex1.c ex1.h
main.o: main.c ex1.h

