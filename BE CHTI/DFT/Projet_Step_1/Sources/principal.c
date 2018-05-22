
#include "stdio.h"

int test(int);

int reelle(short * signal, short k, short * table); 
extern short LeSignal;
extern short TabCos;
extern short TabSin;

int main(){

int resCos[64] ;
int resSin[64] ;
int i, k;

for (i=0;i<63;i++){	
	//i=k;
	resCos[i] =reelle(&LeSignal, i, &TabCos);
	resSin[i] =reelle(&LeSignal, i, &TabSin);

}	


while(1);

}
