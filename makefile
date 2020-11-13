Prog: main.o fonction.o
	gcc main.o fonction.o -o Prog -Wall

main.o: main.c fonction.h
	gcc -c main.c -Wall

fonction.o: fonction.c fonction.h
	gcc -c fonction.c -Wall
	
clean:
	rm -rf *.o
	
deepclean:
	rm -rf *.o main
