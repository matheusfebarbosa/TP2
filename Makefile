TP2: main.o indice.o
	gcc main.o indice.o -o TP2 -Wall -Wextra -Werror -std=c99 -pedantic
main.o: main.c indice.o
		gcc -c main.c -Wall -Wextra -Werror -std=c99 -pedantic
indice.o: indice.c indice.h
		gcc -c indice.c -Wall -Wextra -Werror -std=c99 -pedantic
clean:
	rm *.o TP2