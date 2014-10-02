CC = gcc
args = -O -Wall -lm

all:: test

a4.o : a4.c
	$(CC) $(args) -o a4.o a4.c

test : a4.o
	./a4.o

clean::
	rm a4.o
