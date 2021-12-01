CC=gcc
CFLAGS=-g -Wall
OBJS=main.o scan.o
TARGET=scanner.out

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: defs.h data.h decl.h main.c
scan.o: defs.h data.h decl.h scan.c

clean:
	rm -f scanner *.o
