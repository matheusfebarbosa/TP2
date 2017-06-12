#include <stdio.h>
#include "indice.h"

int main(){

	int d, m;
	int i=0;
	char dirCvs[50], dirInd[50],histAdr[52], indexAdr[56];
	FILE *chat =  NULL;
	FILE *index = NULL;
	int sR,sW;

	scanf("%d %d %s %s", &d, &m, dirCvs, dirInd);
	sprintf(indexAdr,"%sindex",dirInd);
	index = fopen(indexAdr, "w");
	
	
	for(i=1; i<=d; i++){
		sprintf(histAdr,"%s%d",dirCvs,i);
		chat = fopen(histAdr, "r");
		
		updateIndex(&index, &chat, i);

		fclose(chat);
	}
	fclose(index);

	index = fopen(indexAdr, "r");

	createBlocks(&index,m,N_TAPES/2);

	fclose(index);

	index = fopen(indexAdr, "w");

	sR=0;
	sW = N_TAPES/2;
	
	while(merge(N_TAPES/2, sR,sW)!=1){
		if(sW == N_TAPES/2){
			sW=0;
			sR=N_TAPES/2;
		}else{
			sR=0;
			sW = N_TAPES/2;
		}
	}

	copyIndex(&index,sW);

	fclose(index);

	return 0;
}