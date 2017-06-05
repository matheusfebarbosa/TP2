#include <stdio.h>

int main(){

	int d, m;
	int i;
	char dirCvs[50], dirInd[50],histAdr[52], indexAdr[56];
	FILE *chat =  NULL;
	FILE *index = NULL;
	scanf("%d %d %s %s", &d, &m, dirCvs, dirInd);

	sprintf(indexAdr,"%sindex",dirInd,i);
	index = fopen(indexAdr, "w");
	
	for(i=1; i<=d; i++){
		sprintf(histAdr,"%s%d",dirCvs,i);
		chat = fopen(histAdr, "r");
		updateIndex(&index,&chat,m, i);

		//fclose(chat);
	}

	//fclose(index);

	return 0;
}