#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void handler (int sig){
	if (sig == SIGUSR1){
		int a =NULL;
		printf("signal reçu %d\n", sig);
		wait(&a);
		exit(1);
	}

}

int main (){
	int pid;
	sigset_t set;
	sigemptyset(&set);
	sigprocmask(SIG_SETMASK, NULL, &set);

	struct sigaction action;
	action.sa_handler =handler;
	action.sa_flags=0;

	pid=fork();
	int sig=0;

	switch(pid){
		case -1 : 
			printf("erreur\n"); 
			break;

		case 0 : 
			printf("fils\n"); 
			printf("pid pere %d\n", getppid());
			sigaction(SIGUSR1, &action, NULL);
			while(1);
			//printf("je suis tué\n");
			break;

		default : 
			printf("pere \n");
			sleep(1);
			sigaction(SIGUSR1, &action, NULL);
			switch(sig=kill(pid,SIGUSR1)){
				case 0 :
					printf("le processus va être tué\n");		
					break;
				case  -1 :
					printf("Erreur du kill\n");	
			}
			printf("fils tué\n");
			while(1);
			sigaction(SIGUSR1, &action, NULL);
			printf("père tué\n");
	}
	return 0;
}

/*
Pour tuer le père, aller dans un autre terminal et taper kill -USR1 <num_pid_pere>
*/