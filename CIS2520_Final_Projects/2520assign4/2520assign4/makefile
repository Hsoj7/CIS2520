all: avltree.o avltree

avltree.o: avltree.c
	gcc -Wall -std=c99 -pedantic -c avltree.c -o avltree.o

avltree: avltree.o
	gcc -Wall -std=c99 -pedantic avltree.o -o avltree

clean:
	rm *.o
