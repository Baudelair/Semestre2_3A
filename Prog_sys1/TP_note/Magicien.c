#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <math.h>

pthread_mutex_t lockCreation;
pthread_cond_t condCreation;

void initialisation(int x){
	int listeMag[x] ={0};
	int shm = shmget((key_t) key, sizeof(int)*sizeof(listeMag),066|IPC_CREAT);
	int *ptr = shmat(shm, NULL, 0);
	*ptr = listeMag;
}

void* magicien(void* arg){
	long a =(long) arg;
	pthread_mutex_lock(&lockCreation);	//attente de la création de tous les magiciens
	// while(1){
	// 	pthread_cond_wait(&condCreation, &lockCreation);
	// }
	// pthread_mutex_unlock(&lockCreation);

	pthread_exit(NULL);
}


void creerXMagiciens(int x){
	pthread_t threads[x] = {0};

	pthread_mutex_lock(&lockCreation);
	for(int i=0; i<x; i++){
		pthread_create(&threads[i],NULL, magicien, NULL);	//création de x magicien (threads)
	}
	pthread_cond_broadcast(&condCreation);					//tous les magiciens sont créés donc la guerre peut commencer
}


int main(int argc, char const *argv[])
{
	pthread_mutex_init(&lockCreation, NULL);
	pthread_cond_init(&condCreation, NULL);

	int nb_magicien =5;
	creerXMagiciens(nb_magicien);
	*magicien();


	shmdt(ptr);
	shmctl(shm, IPC_RMID, NULL);
	return 0;
}