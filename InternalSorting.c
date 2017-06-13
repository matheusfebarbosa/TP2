#include "InternalSorting.h"

void heapSort(Index *indexes, int n){
	Index aux;
	buildHeap(indexes, n);
	while(n>1){
		aux = indexes[n-1];
		indexes[n-1] = indexes[0];
		indexes[0] = aux;
		n--;
		maxHeapify(indexes, n, 0);
	}
}

void buildHeap(Index *indexes, int n){
	int i;
	for(i=n/2; i>=0; i--){
		maxHeapify(indexes,n,i);
	}	
}

void maxHeapify(Index *indexes, int n, int father){
	int son;
	Index aux;
	
	son= 2*father +1;
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