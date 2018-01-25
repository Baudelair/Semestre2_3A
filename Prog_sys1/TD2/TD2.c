#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

float * px =NULL;

void * boucle(void *arg){

	for(int j=0; j< *(int *)arg;j++){
		printf("%f \n", *px);
		
	}

	
    pthread_exit(NULL);
}

int main()
{
	int M =3;
	float x=1;
	px= &x;


	//Creation d'un thread pour la fonction boucle
	pthread_t tid;
	pthread_create(&tid,NULL,&boucle, &M);


	for(int i=0; i<M ;i++){
		px=NULL;
		printf("i :%d\n",i);
		px = &x;
	}

	//int k = pthread_join(tid,NULL);
	//printf("k : %d",k);
	//pthread_cancel(tid);

	return 0;
}