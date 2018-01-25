
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void * mafonc (void * arg){
	printf("coucou %d", *(int *) arg);
	return NULL;
}

int main (){
	pthread_t tid;
	int i=5;
	int pthread_create(&tid, NULL, mafonc,&i);
	sleep(5);
	return(0);
}
