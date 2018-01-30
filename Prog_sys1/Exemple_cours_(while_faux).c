#include <stdio.h>
#include <pthread.h>

/* nombre de pointeur dans le buffer circulaire */
#define SIZE 5

/* structure de gestion du buffer */
typedef struct {
  pthread_mutex_t buf_lock; /* mutex sur la structure*/
  int start_index; /* index de la premiere donnee valide */
  int nb_elmt; /* nombre d'element valide dans le tampon circulaire */
  void * data[SIZE]; /* buffer circulaire avec SIZE pointeur */
} circ_buf_t;


/******************************************************************/
/*    creation et initialisation d'un buffer ciculaire            */
/* param�tre: - rien                                              */
/* retour:    - un pointeur sur un buffer correctement construit  */
/******************************************************************/
circ_buf_t * new_cb(){
  circ_buf_t *cb;

  /* allocation */
  if (!(cb=(circ_buf_t*)malloc(sizeof(circ_buf_t)))){
    printf("pb allocation\n");
    return (circ_buf_t*)NULL;
  }

  /* initialisation */
  pthread_mutex_init(&(cb->buf_lock),NULL);
  cb->start_index=0;
  cb->nb_elmt=0;

  /* renvoie du buffer circulaire initialise*/
  return(cb);
}



/***************************************************************/
/*            destruction d'un buffer ciculaire                */
/* param�tre: - le pointeur sur le buffer                      */
/* retour:    - NULL          */
/***************************************************************/
circ_buf_t * delete_cb(circ_buf_t * cb){

  /* destruction du mutex et des variables conditionnelles */
  pthread_mutex_destroy(&(cb->buf_lock));
  free(cb);
  
  /* retour d'un pointeur NULL en cas de reaffectation */
  return(NULL);
}


/***************************************************************/
/*           ajout d'un element dans le buffer                 */
/* param�tre: - le pointeur sur le buffer                      */
/*            - le pointeur sur les donnees                    */
/* retour:    - rien                                           */
/***************************************************************/
void put_data_cb(circ_buf_t * cb, void* data){

  /* verrouillage du buffer */
  pthread_mutex_lock(&(cb->buf_lock));
  
  /* attente tant que le buffer est plein */
  while(cb->nb_elmt == SIZE){}
			
  /* ok il y a de la place dans le buffer */
  /* on stocke l'element */
  cb->data[(cb->start_index + cb->nb_elmt)%SIZE]=data;

  /* mise a jour du nombre d'element */
  cb->nb_elmt ++;

  /* deverrouillage du buffer */
  pthread_mutex_unlock(&(cb->buf_lock));
}

/***************************************************************/
/*         extraction d'un element du buffer                   */
/* param�tre: - le pointeur sur le buffer                      */
/* retour:    - le pointeur sur les donnees                    */
/***************************************************************/
void* get_data_cb(circ_buf_t * cb){
  
  void* data; /* les donnes extraites */
  
  /* verrouillage du buffer */
  pthread_mutex_lock(&(cb->buf_lock));
  
  /* attente tant que le buffer est vide */
  while (cb->nb_elmt == 0) {}
  
  /* on recupere l'element */
  data= cb->data[cb->start_index];

  /* mise a jour de l'index et du nombre d'element */
  cb->start_index= (cb->start_index + 1) % SIZE;
  cb->nb_elmt --;

  /* deverrouillage du mutex */
  pthread_mutex_unlock(&(cb->buf_lock));

  /* retour des donnees */
  return(data);
}

void rang_retir(circ_buf_t *buffer){
 int val=100;
 int i;
 
 /* 5 rangements */
 for(i=0;i<5;i++){
   val++;
   printf(" rangement de %d \n",val);
   put_data_cb(buffer,(void*)val);
   sleep(1);
 }
 
 /* 5 retraits */
 for(i=0;i<5;i++){
   printf("donnee recuperee: %d\n",(int)get_data_cb(buffer));
   sleep(1);
 }
 pthread_exit((void*)1);
}

main(){
  int choix=0; 
  int val =0;
  circ_buf_t *buffer;
  pthread_t id_thread;

  printf("mauvaise gestion d'un buffer avec un mutex \n");
  
  /* creation du buffer */
  buffer=new_cb();
  
  /* creation d'un thread faisant 5 rangement puis 5 retrait */
  pthread_create(&id_thread,NULL,(void*)rang_retir,(void*)buffer);

  /* menu de test */
  while(choix != 3){
    val++;
    printf("taper votre choix 1: ajout, 2: retrait, 3: fin \n");
    scanf("%d",&choix);
    if (choix==1){
      printf(" rangement de %d \n",val);
      put_data_cb(buffer,(void*)val);
    }
    if (choix==2)
      printf("donnee recuperee: %d\n",(int)get_data_cb(buffer));
  }
  
  buffer = delete_cb(buffer);
  
}
  
