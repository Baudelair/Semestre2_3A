#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>


int main (){

	int a;
	//declaration sémaphore
	int key =200;
	int semaphore = semget((key_t)key, 1, 0666 |IPC_CREAT);
	//initialisation sémaphore
	int arg =0;
	semctl (semaphore, 0, SETVAL, arg);



	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_flg = 0;

	//Lorsque buf.sem_num est à 0 -> sémaphore prit
	//Lorsque buf.sem_num est à 1 -> sémaphore libre
	//On utilise buf.sem op pour incrémenter ou décrémenter la valeur buf.sem_num

	buf.sem_op = 1;
	semop(semaphore, &buf, 1);

	printf("semaphore : %d\n", semaphore);
	buf.sem_op = -1;

	semop(semaphore, &buf, 1)
	printf("entree\n");
	scanf("%d", &a);
	sleep(5);
	printf("libere\n");
	buf.sem_op = 1;
	semop(semaphore, &buf, 1);
	
	return 0;
}

/*
Problème : un processus a deux fois d'affilés le sémaphore 
Résolution deuw sémaphores -> un pour la lecture
						   -> un pour l'écriture
*/