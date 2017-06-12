#include <stdio.h>
#include <stdlib.h>

typedef struct index{
	char word[20];
	int document;
	int frequency;
	int position;
} Index;


void updateIndex(FILE **index, FILE **data, int file, long *nIndex);
void createBlocks(FILE **index, int memLimit, int nTapes);
void merge(int iTapes, int firstRTape, int firstWTape);
void heapSort(Index *indexes, int n);
void maxHeapify(Index *indexes, int n);
short sLessThan(char *wordA, char *wordB);
short iLessThan(Index *ia, Index *ib);
int min(Index *indexes, int n);
int readNextIndex(FILE **tape, Index *index);
void printIndex(FILE **tape, Index index);