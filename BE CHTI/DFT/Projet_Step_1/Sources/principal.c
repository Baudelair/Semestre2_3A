
#include "stdio.h"

int test(int);

int reelle(short * signal, short k, short * table); 
extern short LeSignal;
extern short TabCos;
extern short TabSin;

int main(){

int resCos[64] ;
int resSin[64] ;
int k;

for (k=0;k<63;k++){	
	//i=k;
	resCos[k] =reelle(&LeSignal, k, &TabCos);
	resSin[k] =reelle(&LeSignal, k, &TabSin);

}	


while(1);

}
