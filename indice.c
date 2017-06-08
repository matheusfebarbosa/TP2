#include "indice.h"

void updateIndex(FILE **index, FILE **data, int memLimit, int file, long *nIndex){
	char palavra[21];
	int count=0, globalCount=0;

	while(!feof(*data)){
		fscanf(*data, "%c", palavra+count);

		if(palavra[count] == ' ' || palavra[count] == '\n')	{
			palavra[count] = '\0';
			fprintf(*index, "%s %d %d %d\n", palavra, file,1, globalCount-count);
			(*nIndex)++;
			count = -1;
		}

		globalCount++;
		count++;
	}
}

void createBlocks(FILE **index, int memLimit, int nTapes){
	int i=0, j=0, maxBuf = memLimit/sizeof(Index);
	Index *indexes = (Index*) malloc(maxBuf* sizeof(Index));
	FILE *tape = NULL;
	char nome[20];

	while(!feof(*index)){
		sprintf(nome,"temp/f%d",j);	
		tape = fopen(nome,"a");
		
		for(i=0; !feof(*index) && i<maxBuf; i++){
			fscanf(*index,"%s", indexes[i].word);
			fscanf(*index,"%d", &(indexes[i].document));
			fscanf(*index,"%d", &(indexes[i].frequency));
			fscanf(*index,"%d", &(indexes[i].position));
		}

		heapSort(indexes, i);

		for(i=0; i<maxBuf-1; i++){
			fprintf(tape, "%s %d %d %d;", indexes[i].word, indexes[i].document,indexes[i].frequency, indexes[i].position);
		}
		fprintf(tape, "%s %d %d %d\n", indexes[maxBuf-1].word, indexes[maxBuf-1].document,indexes[maxBuf-1].frequency, indexes[maxBuf-1].position);
		
		fclose(tape);

		j = (j+1)%nTapes;
	}

}

void merge(FILE **index, int memLimit){
	int maxBuf = memLimit/sizeof(Index);
	int i,j, reset=0, finish = 0;
	FILE *tape = NULL;
	char name[20];
	char c;
	Index *indexes = (Index*) malloc(maxBuf* sizeof(Index));

	for(i=0,j=0; j<maxBuf; i++,j++){
		sprintf(name,"temp/f%d",i);	
		tape = fopen(name,"r");

		fscanf(tape,"%s", indexes[i].word);
		fscanf(tape,"%d", &(indexes[i].document));
		fscanf(tape,"%d", &(indexes[i].frequency));
		fscanf(tape,"%d", &(indexes[i].position));

		fclose(tape);
	}

	while(1){
		j=0;
		reset=1;
		
		
		for(i=0; i<maxBuf; i++){
			if(indexes[i].document!=-1){
				reset=0;
				if(iLessThan(indexes+i,indexes+j))
					j=i;
			}
		}

		if(reset=1){
			for(i=0,j=0; j<maxBuf; i++,j++){
				sprintf(name,"temp/f%d",i);	
				tape = fopen(name,"r");
				if(feof(tape)){
					finish=1;
					break;
				}
				fscanf(tape,"%s", indexes[i].word);
				fscanf(tape,"%d", &(indexes[i].document));
				fscanf(tape,"%d", &(indexes[i].frequency));
				fscanf(tape,"%d", &(indexes[i].position));

				fclose(tape);
			}
			continue;
		}

		fprintf(*index, "%s %d %d %d\n", indexes[j].word, indexes[j].document,indexes[j].frequency, indexes[j].position);

		sprintf(name,"temp/f%d",i);	
		tape = fopen(name,"r");

		fscanf(tape,"%c",&c);
		if(c!='\n'){
			fscanf(tape,"%s", indexes[j].word);
			fscanf(tape,"%d", &(indexes[j].document));
			fscanf(tape,"%d", &(indexes[j].frequency));
			fscanf(tape,"%d", &(indexes[j].position));	
		}else{
			indexes[j].document=-1;
		}
		fclose(tape);

		if(finish)
			break;
	}
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
			if(son+1<n && iLessThan(indexes+son,indexes+son+1)){
				son++;
			}

			if(iLessThan(&aux,indexes+son)){
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

short sLessThan(char *wordA, char *wordB){
	short i=0;
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

short iLessThan(Index *ia, Index *ib){
	short sLess = sLessThan((*ia).word, (*ib).word);
	if(sLess != -1){
		return sLess;
	}else{
		if((*ia).document<(*ib).document){
			return 1;
		}else if((*ia).document>(*ib).document){
			return 0;
		}else{
			(*ia).frequency++;
			(*ib).frequency++;
			if((*ia).position<(*ib).position){
				return 1;
			}else{
				return 0;			
			}
		}
	}
}