#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

float * px =NULL;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void * boucle(void *arg){

	
	for(int j=0; j< *(int *)arg;j++){
		pthread_mutex_lock (&mut);
		printf("*px : %f \n", *px);
		pthread_mutex_unlock(&mut);
		sleep(1);
	}

	
    pthread_exit(NULL);
}

int main()
{
	int max =4;

	float x=2;
	px= &x;


	//Creation d'un thread pour la fonction boucle
	pthread_t tidx;
	pthread_create(&tidx,NULL, &boucle, &max);


	for(int i=0; i<max ;i++){
		pthread_mutex_lock (&mut);
		px=NULL;
		printf("i : %d\n",i);
		px = &x;
		*px = *px +i;
		pthread_mutex_unlock(&mut);
		sleep(1);
		
	}

	//int k = pthread_join(tid,NULL);
	//printf("k : %d",k);
	//pthread_cancel(tid);

	return 0;
}