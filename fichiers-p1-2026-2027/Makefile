OFILES = main.o  SeamCarving.o PNM.o
TARGET = SeamCarving
CC = gcc
CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99

.PHONY: all clean run

LDFLAGS = -lm

all: $(TARGET)
clean:
	rm -f $(OFILES) $(TARGET)
run: $(TARGET)
	./$(TARGET) bd1.pnm bd1-red.pnm 400 50
$(TARGET): $(OFILES)
	$(CC) -o $(TARGET) $(OFILES) $(LDFLAGS)
PNM.o: PNM.c PNM.h
SeamCarving.o: SeamCarving.c PNM.h SeamCarving.h
main.o: main.c SeamCarving.h PNM.h
