#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void * boucle(void *arg){

	for(int j=0; j< *(int *)arg;j++){
		printf("et mon courroux\n");
		sleep(1);
	}

	
    pthread_exit(NULL);
}

int main()
{
	int N,M;
	printf("Nb coucou :\n");
	scanf("%d",&N);
	printf("Nb courroux\n");
	scanf("%d",&M);

	//Creation d'un thread pour la fonction boucle
	pthread_t tid;
	pthread_create(&tid,NULL,&boucle, &M);


	for(int i=0; i<N;i++){
		printf("Coucou \n");
		sleep(1);
	}

	//int k = pthread_join(tid,NULL);
	//printf("k : %d",k);
	pthread_cancel(tid);

	return 0;
}