CC = gcc
args = -O -Wall

all:: test2

robot: robot.c
	$(CC) $(args) robot.c -o robot

test: robot
	@echo "--------------------------------------------------"
	./robot robot.svg 0 10 0 10 0 10 0 10
	@echo "--------------------------------------------------"

test2: robot
	@echo "--------------------------------------------------"
	./robot robot.svg 15 10 60 20 135 30 235 40
	@echo "--------------------------------------------------"

clean::
	rm -f robot robot.svg
