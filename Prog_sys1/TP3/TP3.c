#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define D 10

pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
int res=0;

void* thread_start(void* arg)
{
	//calcul du nouveau V 
	long a = (long) arg;
	for(int m=0; m<D; m++)
	{
		res= res + mat[a][m] * V[k];
	}
	//probleme de retour de la valeur res
	pthread_exit(NULL);
}

int main(void)
{

	mat=[D][D];

	for(int k=0; i < D; i++)
	{
		for(j=0; j < D; j++)
		{
        	t[i][j]=rand()%100;
    	}
	}

	V = [D];

	for(int j=0; j < D; j++)
	{
        V[i]=rand()%100;
    }

	pthread_t threads[D] = {0}; 

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&condition, NULL);

	for (int i = 0; i < D; i++){
		pthread_create(&threads[i], NULL, thread_start, (void *)i);
		//recuperer res thread
		V[i]=res
	} 

	for (int i = 0; i < D; i++) pthread_join(threads[i], NULL);

	return 0;

}



/*
struct parametre{
	int methode;
	int  *vecteur;
	int (matrice)[D];
	int num_collone;
}par;

*/