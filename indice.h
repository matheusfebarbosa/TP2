#include <stdio.h>
#include <stdlib.h>

typedef struct index{
	char word[20];
	int document;
	int frequency;
	int position;
} Index;


void updateIndex(FILE **index, FILE **data, int memLimit, int file, long *nIndex);
void createBlocks(FILE **index, int memLimit, int nTapes);
void merge(FILE **index, int memLimit);
void heapSort(Index *indexes, int n);
void maxHeapify(Index *indexes, int n);
short sLessThan(char *wordA, char *wordB);
short iLessThan(Index *ia, Index *ib);