#include "MyString.h"

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