#include <stdio.h>
#include <pthread.h>

#define nb_esclave 3

typedef struct barrier_struct{
  pthread_mutex_t lock; /* mutex de protection de la structure */
  int n_clients; /* nombre d'intervenant dans la barriere */
  int n_waiting; /* nombre de thread deja bloque sur la barriere */
  int phase; /* alternance pour l'appel successif */
  pthread_cond_t wait_cv; /* attente sur condition */
} barrier_t;

/********************************************************/
/*      variables globales                              */
/********************************************************/
barrier_t *barriere;


/**********************************************************/
/*             creation d'une barriere                    */
/* parametre: - nombre d'adherant a la barriere           */
/* retour: pointeur alloue sur une barriere               */
/**********************************************************/
barrier_t * barrier_init(int nb_client)
{
  barrier_t *barrier;

  /* allocation de la barriere */
  if (!(barrier= (barrier_t *)malloc(sizeof(barrier_t))))
    return (barrier_t*)NULL;

  /* initialisation des champs */
  barrier->n_clients=nb_client;
  barrier->n_waiting=0;
  barrier->phase=0;
  pthread_mutex_init(&(barrier->lock),NULL);
  pthread_cond_init(&(barrier->wait_cv),NULL);
  

  return(barrier);
}


/**********************************************************/
/*       destruction d'une barriere                       */
/* parametre: - la barriere a detruire                    */
/* retour:    - u pointeur NULL                           */
/**********************************************************/
barrier_t* barrier_destroy(barrier_t* barrier)
{
  /* si le pointeur est different de NULL on nettoie */
  if (barrier){
    pthread_mutex_destroy(&(barrier->lock));
    pthread_cond_destroy(&(barrier->wait_cv));
    free(barrier);
  }

  return (barrier_t*)NULL;
}

/******************************************************/
/* fonction implementant le principe de la barriere   */
/* parametre: - la barriere consideree                */
/* retour: rien                                       */
/******************************************************/
void barrier_wait(barrier_t * barrier)
{
  int ma_phase;

  /* protection de la structure */
  pthread_mutex_lock(&barrier->lock);
  
  /* recuperation de l'alternance des barrieres */
  ma_phase= barrier->phase;
  
  /* increment du nombre de clients rentres dans la barriere */
  barrier->n_waiting++;

  /* travail a realiser quand tous les clients sont la */
  if (barrier->n_waiting == barrier->n_clients){
    /* reinitialisation du nombre de client en attente */
    barrier->n_waiting=0;
    /* changement de phase pour eviter que les premiers debloques*/
    /* re-rentre dans la barriere et soit melange avec les clients actuelles */
    barrier->phase = 1-ma_phase;
    /* on previent tout le monde que la condition est vraie: tous les clients
       sont la */
    pthread_cond_broadcast(&barrier->wait_cv);
  }

  /* blocage sur la condition si on est dans la bonne phase */
  while (barrier->phase == ma_phase)
    pthread_cond_wait(&barrier->wait_cv,&barrier->lock);

  /* liberation de la protection sur la structure */
  pthread_mutex_unlock(&barrier->lock);

}

void maitre(){
  /* attente que tous les threads soient la */
  printf("thread %d\n", pthread_self());

 /* distribution du travail aux threads */
  printf("travail distribue \n");
  barrier_wait(barriere);

 

  /* attente des resultats*/
  barrier_wait(barriere ); 

  printf("fin\n");
  pthread_exit(1);
}

void esclave(int eid){ 
  /* attente que tous les threads soient la */
  printf("thread %d escale %d\n", pthread_self(),eid);
  barrier_wait(barriere);
    
  /* travail recu */
  printf("travail\n");
 
  /* envoi des resultats*/
  barrier_wait(barriere ); 

  printf("fin\n");

  pthread_exit(1);
}


main(){

  static int esclav=1;
  pthread_t pthread;
  
  /* creation de la barriere pour le maitre et les esclaves */
  barriere=barrier_init(nb_esclave+1);
  
  /* creation du maitre */
  pthread_create(&pthread,NULL,maitre,NULL);
  
  /* creation des esclaves */
  for(esclav=1;esclav<=nb_esclave;esclav++)
    pthread_create(&pthread,NULL,esclave,esclav);
 
  pthread_exit(1);
}
