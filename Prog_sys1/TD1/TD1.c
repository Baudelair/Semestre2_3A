#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void * boucle(void *arg){

	for(int j=0; j< *(int *)arg;j++){
		printf("et mon courroux\n");
		sleep(1);
	}

	
    pthread_exit(NULL);
}

int main()
{
	int N,M;
	printf("Nb coucou :\n");
	scanf("%d",&N);
	printf("Nb courroux\n");
	scanf("%d",&M);

	//Creation d'un thread pour la fonction boucle
	pthread_t tid;
	pthread_create(&tid,NULL,&boucle, &M);


	for(int i=0; i<N;i++){
		printf("Coucou \n");
		sleep(1);
	}

	//int k = pthread_join(tid,NULL);
	//printf("k : %d",k);
	pthread_cancel(tid);

	return 0;
}



/*
1) Toutes les itérations des boucles for sont réalisées car les threads se finissent en même temps
2) Le thread créé se termine avant la fonction main, donc le thread se quitte et laisse place au processus principale
3) Le processus du main se finit avant et fait un return 0 ce qui tue tous les threads esclaves aux programmes. 
Donc le thread de la fonction boucle ne pourra pas se finir
4) pthread_join va attendre que le thread esclave se termine avant de passer à la ligne suivannte
5) pthread cancel ferme le thread même si il n'est pas encore finis

*/