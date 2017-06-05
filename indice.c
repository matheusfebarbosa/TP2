#include "indice.h"

void updateIndex(FILE **index, FILE **data, int memLimit, int file){
	char palavra[21];
	int count=0, globalCount=0;

	while(!feof(*data)){
		fscanf(*data, "%c", palavra+count);

		if(palavra[count] == ' ' || palavra[count] == '\n')	{
			palavra[count] = '\0';
			fprintf(*index, "%s %d %d %d\n", palavra, file,1, globalCount-count);
			count = 0;
		}else{
			globalCount++;
			count++;
		}

		
	}
}

void sortIndex(FILE **index, FILE **data, int memLimit, int file){
	
}