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

void createBlocks(FILE **index, int memLimit){
	int i=0, j=1, maxBuf = memLimit/sizeof(Index);
	Index *indexes = (Index*) malloc(maxBuf* sizeof(Index));
	FILE *fita = NULL;
	char nome[20];
	printf("show\n");
	while(!feof(*index)){
		sprintf(nome,".temp/f%d",j);	
		fita = fopen(nome,"a");
		printf("%p\n", fita);
		for(i=0; !feof(*index) && i<maxBuf; i++){
			fscanf(*index,"%s", indexes[i].word);
			fscanf(*index,"%d", &(indexes[i].document));
			fscanf(*index,"%d", &(indexes[i].frequency));
			fscanf(*index,"%d", &(indexes[i].position));
		}
		printf("%s\n",nome);
		quickSort(indexes, 0, i);
		printf("show\n");
		for(i=0; i<maxBuf-1; i++){
			printf("daora\n");
			fprintf(fita, "%s %d %d %d;", indexes[i].word, indexes[i].document,indexes[i].frequency, indexes[i].position);
		}
		printf("show\n");
		fprintf(fita, "%s %d %d %d\n", indexes[maxBuf-1].word, indexes[maxBuf-1].document,indexes[maxBuf-1].frequency, indexes[maxBuf-1].position);
		printf("show\n");
		fclose(fita);
		j = maxBuf%(j+1);
	}	
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