CC=gcc
CFLAGS=-g -Wall
OBJS=main.o scan.o tree.o interp.o expr.o gen.o cg.o
TARGET=Compiler2021

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: defs.h data.h decl.h main.c
scan.o: defs.h data.h decl.h scan.c
tree.o: defs.h data.h decl.h tree.c
interp.o = defs.h data.h decl.h interp.c
expr.o = defs.h data.h decl.h expr.c
gen.o = defs.h data.h decl.h gen.c
cg.o = defs.h data.h decl.h cg.c

clean:
	rm -f scanner *.o
	rm -f scanner *.code
