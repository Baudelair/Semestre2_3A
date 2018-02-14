#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t libre = PTHREAD_COND_INITIALIZER;
int ressources = 4;

void * fct1(void * agr){

<<<<<<< HEAD
	pthread_mutex_lock(&mut1);
	while(ressources<3){
=======
	
	while(ressources<=3){
		pthread_mutex_lock(&mut1);
>>>>>>> b2135970f05982b2682f82ecc66707cfba97a92d
		pthread_cond_wait(&libre, &mut1);
		printf("Pas assez de ressources 3\n");
		
	}

	ressources -= 3;
<<<<<<< HEAD
	printf("ressource : 3 prise\n");
	pthread_mutex_unlock(&mut1);

	sleep(1);

	pthread_mutex_lock(&mut1);
=======
	printf("fct 1 finis\n");
	sleep(6);
>>>>>>> b2135970f05982b2682f82ecc66707cfba97a92d
	ressources +=3;
	printf("ressource : 3 libéré\n");

	pthread_cond_broadcast(&libre);
	pthread_mutex_unlock(&mut1);
	pthread_exit(NULL);
}

void * fct2(void * agr){

	
	while(ressources<2){
		pthread_mutex_lock(&mut1);	
		pthread_cond_wait(&libre, &mut1);
		printf("Pas assez de ressources 2\n");
		
	}

	ressources -= 2;
<<<<<<< HEAD
	printf("ressource : 2 prise\n");
	pthread_mutex_unlock(&mut1);

	sleep(1);

	pthread_mutex_lock(&mut1);
	ressources +=2;
	printf("ressource : 2 libéré\n");

=======
	printf("fct 2 finis\n");
	sleep(4);
	ressources += 2;
>>>>>>> b2135970f05982b2682f82ecc66707cfba97a92d
	pthread_cond_broadcast(&libre);
	pthread_mutex_unlock(&mut1);
	pthread_exit(NULL);	
}

void * fct3(void * agr){

	while(ressources<1){
		pthread_mutex_lock(&mut1);
		pthread_cond_wait(&libre, &mut1);
		printf("Pas assez de ressources 1\n");
	}

	ressources -= 1;
<<<<<<< HEAD
	printf("ressource : 1 prise\n");
	pthread_mutex_unlock(&mut1);

	sleep(1);

	pthread_mutex_lock(&mut1);
=======
	printf("fct 3 finis\n");
	sleep(2);
>>>>>>> b2135970f05982b2682f82ecc66707cfba97a92d
	ressources +=1;
	printf("ressource : 1 libéré\n");

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