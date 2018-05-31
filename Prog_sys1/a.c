#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main (void){
  int pid;

  int pidPere = getppid();

  if ((pid = fork()) > 0){
    printf("je suis dans le pere : %d\n", pid);
  }
  else if (pid == 0){
    printf("je suis dans le fils %d\n", pid);
  }
  else {
    printf("erreur fork\n");
  }

  return 0;
}
