TP2: main.o indice.o
	gcc main.o indice.o -o TP2
main.o: main.c indice.o	
		gcc -c main.c
indice.o: indice.c indice.h
		gcc -c indice.c
clean:
	rm *.o TP2