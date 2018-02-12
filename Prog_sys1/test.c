#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#define MAX 200
void handler(int sig){
  printf("signal plus\n");
  pthread_exit(NULL);
}

void* monthread(){
  int i;
  sigset_t ens_signal;
  struct sigaction action;
 
  if (sigfillset(&ens_signal)){
    printf("pb mise a vide ensemble des signaux captures\n");
    exit(-1);
  }
  if (sigdelset(&ens_signal,SIGUSR1)){
    printf("pb ajout SIGUSR1 a l'ensemble des signaux captures\n");
    exit(-1);
  }
  if (pthread_sigmask(SIG_SETMASK, &ens_signal,NULL)){
    printf("pb mise en place du masque\n");
    exit(-1);
  }
  action.sa_handler = handler;
  if(sigaction(SIGUSR1, &action, NULL)){
    printf("pb mise en place du handler\n");
    exit(-1);
  }
  while(1);
  pthread_exit(NULL);
}

int main()
{
  pthread_t thread;

  pthread_create( & thread, NULL,monthread ,NULL);
  sleep(2);
  pthread_kill((pthread_t)getpid(), SIGUSR1);
  pthread_exit(NULL);
  return(0);
}