OFILES1 = mainint.o sort.o
OFILES2 = maincomplex.o sort.o complex.o
TARGET1 = mainint
TARGET2 = maincomplex
CC = gcc
CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic\
         -std=c99

.PHONY: all clean run archive

all: $(TARGET1) $(TARGET2)

clean:
	rm -f $(OFILES1) $(OFILES2) $(TARGET1) $(TARGET2)

archive:
	tar cvfz trigenerique.tar.gz *.h *.c README Makefile

$(TARGET1): $(OFILES1)
	$(CC) $(OFILES1) -o $(TARGET1)  

$(TARGET2): $(OFILES2)
	$(CC) $(OFILES2) -o $(TARGET2) -lm

complex.o: complex.c complex.h
maincomplex.o: maincomplex.c complex.h sort.h
mainint.o: mainint.c sort.h
sort.o: sort.c sort.h

