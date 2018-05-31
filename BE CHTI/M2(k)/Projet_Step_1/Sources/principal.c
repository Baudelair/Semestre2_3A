
#include "stdio.h"

int M2(short * signal, short k); 

extern short LeSignal;

int main(){

		int res[64] ;
		int k;

		for (k=0;k<63;k++){	
			
				res[k] =M2(&LeSignal, k);
		}	


		while(1);

}
