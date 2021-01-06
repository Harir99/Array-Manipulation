CC=gcc 
CFLAGS=-std=c99 -Wall -pedantic -DARRAY

all: array.o

test1: test1.c array.h array.o
	$(CC) $(CFLAGS) test1.c array.o -o test1

test1.o: test1.c array.h
	$(CC) $(CFLAGS) -c test1.c -o test1.o

test2: test2.c array.h array.o
	$(CC) $(CFLAGS) test2.c array.o -o test2

test2.o: test2.c array.h
	$(CC) $(CFLAGS) -c test2.c -o test2.o

test3: test3.c array.h array.o
	$(CC) $(CFLAGS) test3.c array.o -o test3

test3.o: test3.c array.h
	$(CC) $(CFLAGS) -c test3.c -o test3.o

test4: test4.c array.h array.o
	$(CC) $(CFLAGS) test4.c array.o -o test4

test4.o: test4.c array.h
	$(CC) $(CFLAGS) -c test4.c -o test4.o

test5: test5.c array.h array.o
	$(CC) $(CFLAGS) test5.c array.o -o test5

test5.o: test5.c array.h
	$(CC) $(CFLAGS) -c test5.c -o test5.o

test6: test6.c array.h array.o
	$(CC) $(CFLAGS) test6.c array.o -o test6

test6.o: test6.c array.h
	$(CC) $(CFLAGS) -c test6.c -o test6.o

test7: test7.c array.h array.o
	$(CC) $(CFLAGS) test7.c array.o -o test7

test7.o: test7.c array.h
	$(CC) $(CFLAGS) -c test7.c -o test7.o

test8: test8.c array.h array.o
	$(CC) $(CFLAGS) test8.c array.o -o test8

test8.o: test8.c array.h
	$(CC) $(CFLAGS) -c test8.c -o test8.o

array.o: array.c array.h
	$(CC) $(CFLAGS) -c array.c -o array.o

clean:
	rm -f *.o test2
