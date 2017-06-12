#include <stdio.h>
#include "indice.h"

int main(){

	int d, m;
	int i=0;
	char dirCvs[50], dirInd[50],histAdr[52], indexAdr[56];
	FILE *chat =  NULL;
	FILE *index = NULL;
	scanf("%d %d %s %s", &d, &m, dirCvs, dirInd);
	sprintf(indexAdr,"%sindex",dirInd);
	index = fopen(indexAdr, "w");
	long nIndex=0;
	
	for(i=1; i<=d; i++){
		sprintf(histAdr,"%s%d",dirCvs,i);
		chat = fopen(histAdr, "r");
		
		updateIndex(&index, &chat, i, &nIndex);

		fclose(chat);
	}
	fclose(index);

	index = fopen(indexAdr, "r");

	createBlocks(&index,m,nIndex*32/m);

	merge(m/32, 0,m/32);

	fclose(index);

	/*i=0;
	do{
		sprintf(histAdr,"temp/f%d",i);
		i++;
	}while(remove(histAdr)!=-1);*/

	return 0;
}