CC = gcc
args = -O -Wall

all:: test

robot: robot.c
	$(CC) $(args) robot.c -o robot

test: robot
	@echo "--------------------------------------------------"
	@./robot robot.svg 0 0 0 0
	@echo "--------------------------------------------------"

test2: robot
	@echo "--------------------------------------------------"
	@./robot robot.svg 15 60 135 235
	@echo "--------------------------------------------------"

clean::
	rm -f robot robot.svg
