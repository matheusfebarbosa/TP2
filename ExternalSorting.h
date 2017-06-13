#include "InternalSorting.h"

#define MAX_TAPES 20

void updateIndex(FILE **index, FILE **data, int file);
void createBlocks(FILE **index, int memLimit, int nTapes);
int merge(int iTapes, int firstRTape, int firstWTape);
void copyIndex(FILE **index, int nTape);