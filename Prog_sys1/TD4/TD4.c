#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_key_t key;

//pthread_cond_t libre = PTHREAD_COND_INITIALIZER;

void  fonction_init(){
	pthread_key_create(&key, NULL);
	printf("Initialisation\n");
	sleep(1);
	printf("Executé \n");
}

int incrementation(int self){

	int k=pthread_getspecific(&key);
	k++;
	return k;
}

void * fct1(void *agr){
	int *p;
	p= pthread_self();
	pthread_setspecific(&key, *p);
	for (int i=0; i<3;i++){
		pthread_once(&once,fonction_init);
		printf("k = %d\n", incrementation(*p));
	}

	pthread_exit(NULL);
}

void * fct2(void *agr){

	int *q;
	q = pthread_self();
	pthread_setspecific(&key, *q);
	for (int i=0; i<3;i++){
		pthread_once(&once,fonction_init);
		printf("k = %d\n", incrementation(*q));
	}
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{

	//Condition
	//pthread_cond_init(&libre,NULL);

	//Déclaration mutex
	pthread_t tid1;
	pthread_t tid2;

	

	pthread_create(&tid1,NULL, &fct1, NULL);
	pthread_create(&tid2,NULL, &fct2, NULL);

	//thread principale
	int *r;
	r = pthread_self();
	pthread_setspecific(&key, *r);
	for (int i=0; i<3;i++){
		pthread_once(&once,fonction_init);
		printf("k = %d\n", incrementation(*r));
	}


	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	
	return 0;
}