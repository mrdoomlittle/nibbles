ARC=ARC64
MDLINT_INC=/usr/local/include
all:
	gcc -c -std=c11 -D__$(ARC) -I$(MDLINT_INC) -o nibbles.o nibbles.c
	ar rcs lib/libmdl-nibbles.a nibbles.o
	cp nibbles.h inc/mdl

main: all
	gcc -std=c11 -D__$(ARC) -Iinc -Llib -o main main.c -lmdl-nibbles

clean:
	rm -f inc/mdl/*.h lib/*.a *.o main
