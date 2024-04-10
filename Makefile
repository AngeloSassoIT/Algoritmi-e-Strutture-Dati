main : main.c	Makefile
		
	gcc -ansi -Wall -O main.c -o main -lm

pulisci:
	rm -f main.c
	
