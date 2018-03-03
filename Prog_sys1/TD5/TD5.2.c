#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 6

void handler (int sig){
	switch(sig){
		case -1 : 
			printf("erreur\n"); 
			break;

		case SIGUSR1 : 
			sigaction(SIGUSR1, &action, NULL);
			break;

		case SIGUSR2 : 
			sleep(1);
			sigaction(SIGUSR2, &action, NULL);
	}

}

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
	sigset_t set;
	sigemptyset(&set);
	sigprocmask(SIG_SETMASK, NULL, &set);

	struct sigaction action;
	action.sa_handler =handler;
	action.sa_flags=0;

	pid=fork();
	int sig=0;

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