
#include "stdio.h"

int carre(int);

int M2(short * signal, short k); 

extern short LeSignal;
extern short TabCos;
extern short TabSin;

int main(){

int res[64] ;
int i;

for (i=0;i<63;i++){	
	
	res[i] =M2(&LeSignal, i);
}	




while(1);

}
