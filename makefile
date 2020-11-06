Prog: main.o fonction.o
	gcc main.o fonction.o -o Prog

main.o: main.c fonction.h
	gcc -c main.c

fonction.o: fonction.c fonction.h
	gcc -c fonction.c
