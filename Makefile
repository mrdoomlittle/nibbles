ARC=-DARC64
#EINT_T_INC=
all:
	gcc -c -std=c11 $(ARC) -o nibbles.o nibbles.c
	ar rcs lib/libnibbles.a nibbles.o
	cp nibbles.h inc

main: all
	g++ -std=c++11 $(ARC) -Iinc -Llib -o main main.cpp -lnibbles

clean:
	rm -f inc/*.h lib/*.a *.o main
