CC = gcc
args = -O -Wall

all:: test

robot: robot.c
	@$(CC) $(args) robot.c -o robot

test: robot
	@echo "--------------------------------------------------"
	@./robot robot.svg 0 0 0 0
	@echo "--------------------------------------------------"

clean::
	rm -f robot robot.svg
