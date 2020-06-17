all: q1.o q2.o run1 run2

q1.o:	q1.c
	gcc -Wall -std=c99 -pedantic -c q1.c -o q1.o

q2.o:	q2.c
	gcc -Wall -std=c99 -pedantic -c q2.c -o q2.o

run1: q1.o
	gcc -Wall -std=c99 -pedantic q1.o -o run1

run2: q2.o
	gcc -Wall -std=c99 -pedantic q2.o -o run2

clean:
	rm *.o
