CC = gcc
args = -O -Wall -lm

all:: testQuad

quad.o: quad.c
	$(CC) $(args) -o quad.o quad.c

cubic.o: cubic.c
	$(CC) $(args) -o cubic.o cubic.c

testQuad: quad.o
	./quad.o image.svg 45 275 150 30 255 275

testCubic: cubic.o
	./cubic.o image.svg 45 150 45 25 255 275 255 150

clean::
	rm quad.o cubic.o image.svg
