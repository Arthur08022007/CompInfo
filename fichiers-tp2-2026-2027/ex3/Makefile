OFILES = percolation.o
TARGET = percolation
CC = gcc
CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99

.PHONY: all clean run runwin

all: $(TARGET)

clean:
	rm -f $(OFILES) $(TARGET)

run: $(TARGET)
	./$(TARGET)

runwin: $(TARGET)
	$(TARGER).exe

$(TARGET): $(OFILES)
	$(CC) -o $(TARGET) $(OFILES)
