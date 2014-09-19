CC = gcc
args = -O -Wall

all:: test2

robot.o: robot.c
	$(CC) $(args) robot.c -o robot.o

test: robot.o
	@echo "--------------------------------------------------"
	./robot.o robot.svg 0 10 0 10 0 10 0 10
	@echo "--------------------------------------------------"

test2: robot.o
	@echo "--------------------------------------------------"
	./robot.o robot.svg 30 10 -90 15 135 20 235 25
	@echo "--------------------------------------------------"

clean::
	rm -f robot.o robot.svg
