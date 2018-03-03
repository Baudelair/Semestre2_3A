#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <math.h>

#define MAX 1000


int main (){
	int pid;

	int i =0;

	int pipe_fils[2];
	int pipe_pere[2];

	//tube du pere vers le fils
	pipe(pipe_fils);
	/*close(pipe_pere[1]);
	close(pipe_fils[0]);*/

	//tube du fils vers le pere
	pipe(pipe_pere);
	/*close(pipe_pere[0]);
	close(pipe_fils[1]);*/

	pid=fork();

	int entier=0;

	struct timeval debut;
	struct timeval arrivee;


	switch(pid){
		case -1 : 
			printf("Erreur\n"); 
			break;

		case 0 : 
			printf("fils\n"); 
			printf("pid fils %d\n", getpid());
			read(pipe_fils[0], &entier,sizeof(int));
			sleep(1);

			while(i<MAX){
				read(pipe_fils[0], &entier,sizeof(int));
				//printf("reçu fils : %d\n", entier);
				entier++;
				write(pipe_pere[1], &entier,sizeof(int));
				//printf("envoyer fils : %d\n", entier);
				i++;
			}

			close(pipe_pere[1]);
			close(pipe_fils[0]);

			break;

		default : 
			printf("pere pid : %d\n", getpid());
			gettimeofday(&debut, NULL);
			write(pipe_fils[1], &entier, sizeof(int));

			while(i<MAX){
				write(pipe_fils[1], &entier, sizeof(int));
				//printf("envoyer père : %d\n", entier);					
				read(pipe_pere[0], &entier, sizeof(int));
				//printf("reçu père : %d\n", entier);
				i++;
				entier++;
			}

			gettimeofday(&arrivee, NULL);

			long tempsd = debut.tv_sec*pow(10, -6) + debut.tv_usec;
			long tempsa = arrivee.tv_sec*pow(10, -6) + arrivee.tv_usec;
			long temps = tempsa - tempsd;
			printf("Temps : %ld us\n", temps);

			long debit = ((1000*2*4*8)*pow(10, -6))/ temps;
			printf("Débit : %ld Mb/s\n", debit);
			close(pipe_pere[0]);
			close(pipe_fils[1]);
			break;

	}
	
	return 0;
}

/*
Pour tuer le père, aller dans un autre terminal et taper kill -USR1 <num_pid_pere>
*/