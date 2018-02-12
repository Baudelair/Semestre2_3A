#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t libre = PTHREAD_COND_INITIALIZER;
int ressources = 4;

void * fct1(void * agr){

	pthread_mutex_lock(&mut1);
	while(ressources<=3){
		pthread_cond_wait(&libre, &mut1);
		printf("Pas assez de ressources 3\n");
		
	}
	
	ressources -= 3;
	printf("fct 1 finis\n");
	sleep(3);
	ressources +=3;
	pthread_cond_broadcast(&libre);
	pthread_mutex_unlock(&mut1);
	pthread_exit(NULL);
}

void * fct2(void * agr){

	pthread_mutex_lock(&mut1);	
	while(ressources<2){
		pthread_cond_wait(&libre, &mut1);
		printf("Pas assez de ressources 2\n");
		
	}

	
	ressources -= 2;
	printf("fct 2 finis\n");
	sleep(3);
	ressources += 2;
	pthread_cond_broadcast(&libre);
	pthread_mutex_unlock(&mut1);
	pthread_exit(NULL);	
}

void * fct3(void * agr){

	pthread_mutex_lock(&mut1);
	while(ressources<1){
		pthread_cond_wait(&libre, &mut1);
		printf("Pas assez de ressources 1\n");
	}

	
	ressources -= 1;
	printf("fct 3 finis\n");
	sleep(3);
	ressources +=1;
	pthread_cond_broadcast(&libre);
	pthread_mutex_unlock(&mut1);
	pthread_exit(NULL);
}


int main()
{
	

	//Condition
	pthread_cond_init(&libre,NULL);

	//Déclaration mutex
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;

	pthread_create(&tid1,NULL, &fct1, &ressources);
	pthread_create(&tid2,NULL, &fct2, &ressources);
	pthread_create(&tid3,NULL, &fct3, &ressources);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	return 0;
}