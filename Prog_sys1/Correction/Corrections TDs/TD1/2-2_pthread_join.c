#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gestion_erreur.h"

typedef void *(*fct_ptr_t)(void *);     /* Type pointeur de fonction */

void affiche_courroux(int *N)
{
    for(int i = 0; i < *N; i++) {
        printf("et mon courroux\n");
        sleep(1);
    }

    /* Attention de ne pas renvoyer l'adresse d'une variable locale ! */
    int *retval = malloc(sizeof(int));
    ERROR_IF(retval == NULL, "Erreur malloc");

    *retval = 1337;
    pthread_exit(retval);
}

int main(int argc, char **argv)
{
    pthread_t t_id;
    int M,N,err;
    int *retval = NULL;

    ERROR_IF(argc != 3, "As tu oublié les 2 arguments ?");
    M = atoi(argv[1]);
    N = atoi(argv[2]);

    err = pthread_create(&t_id, NULL, (fct_ptr_t)affiche_courroux, &N);
    ERROR_IF(err != 0, "Erreur pthread_create");

    for(int i = 0; i < M; i++) {
        printf("coucou\n");
        sleep(1);
    }

    /* Attente du thread et récupération de la valeur de retour */
    err = pthread_join(t_id, (void**)&retval);
    ERROR_IF(err != 0, "Erreur pthread_join");

    printf("Valeur retournée=%d\n",*retval);
    free(retval);

    return EXIT_SUCCESS;
}
