#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t condition;

int resources = 4;

void* thread_start(void* arg)
{
	long res = (long) arg;
	pthread_t self = pthread_self();
	
	pthread_mutex_lock(&lock);
	while (res > resources)
	{
		pthread_cond_wait(&condition, &lock);
	}
	resources -= res;
	printf("Thread %u took %d resources\n", self, res);
	printf("=== %d resources available ===\n", resources);
	pthread_mutex_unlock(&lock);

	sleep(1);

	pthread_mutex_lock(&lock);
	resources += res;
	printf("Thread %u freed %d resources\n", self, res);
	printf("=== %d resources available ===\n", resources);
	pthread_cond_broadcast(&condition);
	pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
}

int main(void)
{
	pthread_t threads[3] = {0}; 
	unsigned int i;

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&condition, NULL);

	printf("=== %d resources available ===\n", resources);
	pthread_create(&threads[0], NULL, thread_start, (void*) 3);
	pthread_create(&threads[1], NULL, thread_start, (void*) 2);
	pthread_create(&threads[2], NULL, thread_start, (void*) 1);

	for (i = 0; i < 3; i++) pthread_join(threads[i], NULL);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&condition);
}
