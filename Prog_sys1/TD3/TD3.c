#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void * fct1(void * agr){
	printf("fct 1 finis\n");
	sleep(4);
}

void * fct2(void * agr){
	printf("fct 2 finis\n");
	sleep(4);	
}

void * fct3(void * agr){
	printf("fct 3 finis\n");
	sleep(4);
}


int main()
{
	ressources = 4;

	res_fct1= 3;
	res_fct2= 2;
	res_fct3= 1;


	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;


	pthread_create(&tid1,NULL, &fct1, &max);
	pthread_create(&tid2,NULL, &fct2, &max);
	pthread_create(&tid3,NULL, &fct3, &max);
	return 0;
}