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
	int i=0, j=0, maxBuf = memLimit/sizeof(Index);
	Index *indexes = (Index*) malloc(maxBuf* sizeof(Index));
	FILE *fita = NULL;
	char nome[20];

	while(!feof(*index)){
		sprintf(nome,"temp/f%d",j);	
		fita = fopen(nome,"a");
		
		for(i=0; !feof(*index) && i<maxBuf; i++){
			fscanf(*index,"%s", indexes[i].word);
			fscanf(*index,"%d", &(indexes[i].document));
			fscanf(*index,"%d", &(indexes[i].frequency));
			fscanf(*index,"%d", &(indexes[i].position));
		}

		heapSort(indexes, i);

		for(i=0; i<maxBuf-1; i++){
			fprintf(fita, "%s %d %d %d;", indexes[i].word, indexes[i].document,indexes[i].frequency, indexes[i].position);
		}
		fprintf(fita, "%s %d %d %d\n", indexes[maxBuf-1].word, indexes[maxBuf-1].document,indexes[maxBuf-1].frequency, indexes[maxBuf-1].position);
		
		fclose(fita);

		j = (j+1)%maxBuf;
	}

}

void merge(FILE **index, int memLimit){

}

void heapSort(Index *indexes, int n){
	Index aux;
	while(n>1){
		maxHeapify(indexes, n);
		aux = indexes[n-1];
		indexes[n-1] = indexes[0];
		indexes[0] = aux;
		n--;
	}
}

void maxHeapify(Index *indexes, int n){
	int father, son, i;
	Index aux;
	for(i=n/2; i>=0; i--){
		father=i;
		son= 2*i +1;
		aux = indexes[father];

		while(son<n){
			if(son+1<n && less(indexes[son].word,indexes[son+1].word)){
				son++;
			}

			if(less(aux.word,indexes[son].word)){
				indexes[father] = indexes[son];
				father = son;
				son = 2*father +1;
			}else{
				break;
			}
		}

		indexes[father] = aux;
	}	
}

int less(char *wordA, char *wordB){
	int i=0;
	while(wordA[i]!='\0' && wordB[i]!='\0'){
		if(((int) wordA[i]) < ((int) wordB[i])){
			return 1;
		}else if(((int) wordB[i]) < ((int) wordA[i])){
			return 0;
		}else{
			i++;
		}
	}

	if(wordA[i]=='\0' && wordB[i]=='\0'){
		return -1;
	}else if (wordA[i]=='\0' && wordB[i]!='\0'){
		return 1;
	}else{
		return 0;
	}
}