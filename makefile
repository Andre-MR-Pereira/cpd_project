all: ballAlg
 
ballAlg: main.o
	gcc -o ballAlg main.o

main.o: ballAlg.c
	gcc -o main.o ballAlg.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~ ball