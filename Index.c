#include "Index.h"

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
	fprintf(*tape, "%.20s%c%d%c%d%c%d",index.word,
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