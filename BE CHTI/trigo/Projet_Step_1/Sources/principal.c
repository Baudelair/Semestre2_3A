
#include "stdio.h"

int test(int);

int main(){
int pos=0;	
int max =0;
int min = 32767;
int res = 0;
	
	
for (int i=0;i<63;i++){	
	res =test(pos);
	if (min>res){
		min = res;
	}
	if (max<res){
		max = res;
	}
	pos++;
}	
printf("min : %d, max ; %d", min, max);

while(1);

}
