#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

float * px =NULL;

void * boucle(void *arg){

	for(int j=0; j< *(int *)arg;j++){
		printf("%f \n", *px);
		sleep(1);
	}

	
    pthread_exit(NULL);
}

int main()
{
	int max =3;
	float x=1;
	px= &x;

	printf("px : %d\n",px);
	//Creation d'un thread pour la fonction boucle
	pthread_t tid;
	pthread_create(&tid,NULL,&boucle, &max);


	for(int i=0; i<max ;i++){
		px=NULL;
		printf("px : %d\n",px);
		printf("i : %d\n",i);
		px = &x;
		printf("px : %d\n",px);
		sleep(1);
	}

	//int k = pthread_join(tid,NULL);
	//printf("k : %d",k);
	//pthread_cancel(tid);

	return 0;
}