#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 6

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void libere (void * arg){
	if (&mut){
		pthread_mutex_unlock(&mut);
	}
}

void *fct (void *arg)
{
	pthread_mutex_lock(&mut);
	pthread_cleanup_push(libere, NULL);
	printf("j'ai le mutex \n");
	for (int i=0; i< MAX; i++)
	{
		pthread_t b=pthread_self();
		printf("tid fct : %ld\n", b);
		sleep(1);
	}
	
	pthread_mutex_unlock(&mut);
	pthread_cleanup_pop(1);
	pthread_exit(NULL);

}


int main()
{
	pthread_t tid;
	for (int i=0; i<2; i++)
	{
		pthread_create(&tid,NULL, &fct, NULL);
		for (int j=0; j< MAX/2; j++)
		{
			pthread_t a=pthread_self();
			printf("tid main : %ld\n", a);
			sleep(1);
		}

		pthread_cancel(tid);
		sleep(1);

	}

	return 0;
}

//le premier pthread lock le mutex ne laissant pas la place à l'autre pthread de s'éxecuter
