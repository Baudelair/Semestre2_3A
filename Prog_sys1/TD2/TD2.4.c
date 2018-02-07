#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

float * px =NULL;
float * py =NULL;

pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;

void * bouclex(void *arg){

	
	for(int j=0; j< *(int *)arg;j++){
		pthread_mutex_lock (&mut1);
		printf("x) *px : %f \n", *px);
		*px= *px +2;
		pthread_mutex_unlock(&mut1);
		sleep(1);
	}

	
    pthread_exit(NULL);
}

void * boucley(void *arg){

	
	for(int j=0; j< *(int *)arg;j++){
		pthread_mutex_lock (&mut2);
		printf("y) *py : %f \n", *py);
		*py=*py +2;
		pthread_mutex_unlock(&mut2);
		sleep(1);
	}

	
    pthread_exit(NULL);
}


void * bouclexy(void *arg){


	while (1){
		pthread_mutex_trylock (&mut1);
		pthread_mutex_trylock (&mut2);
		for(int j=0; j< *(int *)arg;j++){
			printf("*px : %f et *py : %f \n", *px, *py);
			*px= *px +2;
			*py=*py +2;
			pthread_mutex_unlock(&mut1);
			pthread_mutex_unlock(&mut2);
			sleep(1);
			printf("j : %d\n", j);
		}
	pthread_exit(NULL);
	}
}

int main()
{
	int max =4;

	float x=1;
	px= &x;

	float y=2;
	py=&y;

	//Creation d'un thread pour la fonction boucle
	pthread_t tidx;
	pthread_create(&tidx,NULL, &bouclex, &max);

	//Création d'un thread avec comme variable py
	pthread_t tidy;
	pthread_create(&tidy,NULL, &boucley, &max);

	pthread_t tidxy;
	pthread_create(&tidxy, NULL, &bouclexy, &max);

	pthread_join(tidx,NULL);
	pthread_join(tidy,NULL);
	pthread_join(tidxy, NULL);
	return 0;
}