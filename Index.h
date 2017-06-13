#include <stdio.h>
#include <stdlib.h>
#include "MyString.h"

typedef struct index{
	char word[20];
	int document;
	int frequency;
	int position;
} Index;


short iLessThan(Index *ia, Index *ib);
int min(Index *indexes, int n);
int readNextIndex(FILE **tape, Index *index);
void printIndex(FILE **tape, Index index, char append);