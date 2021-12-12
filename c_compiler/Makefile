CC=gcc
CFLAGS=-g -Wall
OBJS=main.o scan.o tree.o interp.o expr.o
TARGET=scanner.out

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: defs.h data.h decl.h main.c
scan.o: defs.h data.h decl.h scan.c
tree.o: defs.h data.h decl.h tree.c
interp.o = defs.h data.h decl.h interp.c
expr.o = defs.h data.h decl.expr.c

clean:
	rm -f scanner *.o
	rm -f scanner *.out
