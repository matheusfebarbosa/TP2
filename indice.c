#include "indice.h"

void updateIndex(FILE **index, FILE **data, int file){
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

void createBlocks(FILE **index, int memLimit, int nTapes){
	unsigned int i=0, j=0, k=0;
	Index *indexes = (Index*) malloc((memLimit/sizeof(Index))* sizeof(Index));
	FILE *tape = NULL;
	char nome[20];

	while(!feof(*index)){
		sprintf(nome,"tmp/f%d",j);	
		tape = fopen(nome,"a");
		
		for(i=0; i<memLimit/sizeof(Index); i++){
			if(readNextIndex(index,&indexes[i])!=4)
				break;
		}

		heapSort(indexes, i);

		for(k=0; k<i-1; k++){
			printIndex(&tape, indexes[k], ' ');
			fprintf(tape, ";");
		}
		printIndex(&tape, indexes[k], ' ');
		fprintf(tape, "\n");
		
		fclose(tape);

		j = (j+1)%nTapes;
	}

	free(indexes);
}

int merge(int iTapes, int firstRTape, int firstWTape){
	int i,j=-1,menor;
	short rebuild=0,ordering=1, nMerges=0;
	char name[20], op=' ';
	FILE **tapes = (FILE**) malloc(iTapes* sizeof(FILE*));
	FILE *write = NULL;
	Index *indexes = calloc(iTapes,sizeof(Index));
	
	for(i=firstRTape; i<firstRTape+iTapes; i++){
		sprintf(name,"tmp/f%d",i);	
		tapes[i-firstRTape] = fopen(name,"r");
	}

	while(ordering || rebuild){
		if(rebuild<=0){
			for(i=firstRTape; i<firstRTape+iTapes && tapes[i-firstRTape]!=NULL; i++){
				if(readNextIndex(&tapes[i-firstRTape], &indexes[i-firstRTape])!=4){
					break;
				}
				rebuild++;     
			}

			if(rebuild<iTapes){
				if(rebuild==0){
					break;
				}
				ordering=0;
			}

			j = (j+1)%(iTapes);	
			sprintf(name,"tmp/f%d",j+firstWTape);	
			write = fopen(name,"a");
			
		}

		menor = min(indexes,iTapes);
		printIndex(&write, indexes[menor], ' ');		
		fscanf(tapes[menor],"%c",&op);

		if(op==';'){
			readNextIndex(&tapes[menor], &indexes[menor]);
			fprintf(write, ";");
		}else{
			indexes[menor].frequency=-1;
			rebuild--;
			if(rebuild<=0){
				nMerges++;
				fprintf(write, "\n");			
				fclose(write);
			}else{
				fprintf(write, ";");
			}
		}
	}

	for(i=firstRTape; i<firstRTape+iTapes; i++){
		if(tapes[i-firstRTape]!=NULL){
			sprintf(name,"tmp/f%d",i);
			remove(name);
			fclose(tapes[i-firstRTape]);
		}
	}

	free(indexes);

	return nMerges;
}

void copyIndex(FILE **index, int nTape){
	char name[20],c;
	int count=1,i;
	Index actual, prox;
	FILE *rTape = NULL, *cTape = NULL;
	
	sprintf(name,"tmp/f%d",nTape);	
	
	rTape = fopen(name,"r");
	cTape = fopen(name,"r");

	readNextIndex(&cTape, &actual);
	fscanf(cTape, "%c",  &c);
	while(1){
		readNextIndex(&cTape, &prox);
		
		if(!feof(cTape) && sLessThan(actual.word,prox.word)==-1 && actual.document == prox.document){
			count++;
		}else{
			for(i=0; i<count; i++){
				readNextIndex(&rTape, &actual);
				fscanf(rTape, "%c",  &c);
				actual.frequency = count;
				printIndex(index, actual, ',');
				fprintf(*index, "\n");
			}
			if(feof(cTape))
				break;
			count=1;
		}

		actual = prox;
		fscanf(cTape, "%c",  &c);
	}

	remove(name);
	fclose(cTape);
	fclose(rTape);
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
			if((*ia).position<(*ib).position){
				return 1;
			}else{
				return 0;			
			}
		}
	}
}

int readNextIndex(FILE **tape, Index *index){
	return fscanf(*tape,"%s %d %d %d", index->word,
		&(index->document),
		&(index->frequency),
		&(index->position));
}

void printIndex(FILE **tape, Index index, char append){
	fprintf(*tape, "%s%c%d%c%d%c%d", index.word,
			append, 
			index.document,
			append,
			index.frequency, 
			append,
			index.position);
}

int min(Index *indexes, int n){
	int i,menor=-1;
	for(i=0; i<n; i++){
		if(indexes[i].frequency==-1 || indexes[i].frequency==0){
			continue;
		}
		if(menor==-1 || iLessThan(&indexes[i],&indexes[menor])){
			menor=i;
		}
	}
	return menor;
}