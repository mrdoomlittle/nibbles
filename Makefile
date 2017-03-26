all:
	gcc -c -std=c11 -o nibbles.o nibbles.c
	ar rcs lib/libnibbles.a nibbles.o
	cp nibbles.h inc

main: all
	g++ -std=c++11 -Iinc -Llib -o main main.cpp -lnibbles

clean:
	rm -f inc/*.h lib/*.a *.o main
