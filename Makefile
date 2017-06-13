TP2: main.o ExternalSorting.o InternalSorting.o Index.o MyString.o
	gcc main.o ExternalSorting.o InternalSorting.o Index.o MyString.o -o TP2 -Wall -Wextra -Werror -std=c99 -pedantic
main.o: main.c ExternalSorting.o InternalSorting.o Index.o MyString.o
		gcc -c main.c -Wall -Wextra -Werror -std=c99 -pedantic
ExternalSorting.o: ExternalSorting.c ExternalSorting.h InternalSorting.o Index.o MyString.o
			gcc -c ExternalSorting.c -Wall -Wextra -Werror -std=c99 -pedantic
InternalSorting.o: InternalSorting.c InternalSorting.h Index.o MyString.o
				gcc -c InternalSorting.c -Wall -Wextra -Werror -std=c99 -pedantic
Index.o: Index.c Index.h MyString.o
					gcc -c Index.c -Wall -Wextra -Werror -std=c99 -pedantic
MyString.o: MyString.c MyString.h 
						gcc -c MyString.c -Wall -Wextra -Werror -std=c99 -pedantic		
clean:
	rm *.o TP2