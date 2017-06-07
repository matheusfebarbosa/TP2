#include <stdio.h>
#include <stdlib.h>

typedef struct index{
	char word[20];
	int document;
	int frequency;
	int position;
} Index;


void updateIndex(FILE **index, FILE **data, int memLimit, int file);
void createBlocks(FILE **index, int memLimit);
void quickSort(Index *indexes, int front, int back);
char* min(char *wordA, char *wordB);