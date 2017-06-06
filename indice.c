#include "indice.h"

void updateIndex(FILE **index, FILE **data, int memLimit, int file){
	char palavra[21];
	int count=0, globalCount=0;

	while(!feof(*data)){
		fscanf(*data, "%c", palavra+count);

		if(palavra[count] == ' ' || palavra[count] == '\n')	{
			palavra[count] = '\0';
			fprintf(*index, "%s %d %d %d\n", palavra, file,1, globalCount-count);
			count = -1;
		}

		globalCount++;
		count++;
	}
}

void sortIndex(FILE **index, int memLimit, int file){
	int i, maxBuf = memLimit/sizeof(Index);
	Index *indexes = (Index*) malloc(maxBuf* sizeof(Index));
	for(i=0; i<maxBuf; i++){
		fscanf(*index,"%s", indexes[i].word);
		fscanf(*index,"%d", &(indexes[i].document));
		fscanf(*index,"%d", &(indexes[i].frequency));
		fscanf(*index,"%d", &(indexes[i].position));
	} 

	quickSort(indexes, 0, maxBuf);
}

void quickSort(Index *indexes, int front, int back){
	char *pivo = min(indexes[0].word,indexes[back].word);
	int i = front, j=back;

	while(0){

	}

}

char* min(char *wordA, char *wordB){
	int i=0;
	while(wordA[i]!='\0' && wordB[i]!='\0'){
		if(((int) wordA[i]) < ((int) wordB[i])){
			return wordA;
		}else if(((int) wordB[i]) < ((int) wordA[i])){
			return wordB;
		}else{
			i++;
		}
	}
}