#include <mictcp.h>
#include <api/mictcp_core.h>
/* ------------------Partie Perso -----------------------------------*/

struct mic_tcp_sock Sock;


/* -------------------------------------------------------------------*/
/*
 * Permet de créer un socket entre l’application et MIC-TCP
 * Retourne le descripteur du socket ou bien -1 en cas d'erreur
 */

int mic_tcp_socket(start_mode sm) 
{
   int result = -1;
   printf("[MIC-TCP] Appel de la fonction: ");  printf(__FUNCTION__); printf("\n");
   result = initialize_components(sm); /* Appel obligatoire */
 /* ------------------Partie perso ------------------------------------*/
   if(result==-1)
   {
		return -1;
   }			
   set_loss_rate(0);

	Sock.fd = 0;   //Descripteur du socket (int) penser à incrémenter à chaque nouveau sock
	Sock.state = IDLE;

   return Sock.fd;
/* --------------------------------------------------------------------*/
}



/*
 * Permet d’attribuer une adresse à un socket. 
 * Retourne 0 si succès, et -1 en cas d’échec
 */
int mic_tcp_bind(int socket, mic_tcp_sock_addr addr)
{
   printf("[MIC-TCP] Appel de la fonction: ");  printf(__FUNCTION__); printf("\n");
/* ------------------Partie Perso -----------------------------------*/

	if(Sock.fd==socket)
	{
		Sock.addr=addr;
		return 0;
	}
	return -1;
/* -------------------------------------------------------------------*/
}

/*
 * Met le socket en état d'acceptation de connexions
 * Retourne 0 si succès, -1 si erreur
 */
int mic_tcp_accept(int socket, mic_tcp_sock_addr* addr)
{
    printf("[MIC-TCP] Appel de la fonction: ");  printf(__FUNCTION__); printf("\n");
	return -1;
}

/*
 * Permet de réclamer l’établissement d’une connexion
 * Retourne 0 si la connexion est établie, et -1 en cas d’échec
 */
int mic_tcp_connect(int socket, mic_tcp_sock_addr addr)
{  
    printf("[MIC-TCP] Appel de la fonction: ");  printf(__FUNCTION__); printf("\n");
    return -1;
}

/*
 * Permet de réclamer l’envoi d’une donnée applicative
 * Retourne la taille des données envoyées, et -1 en cas d'erreur
 */
int mic_tcp_send (int mic_sock, char* mesg, int mesg_size)
{
    printf("[MIC-TCP] Appel de la fonction: "); printf(__FUNCTION__); printf("\n");
/* ------------------Partie Perso -----------------------------------*/


	struct mic_tcp_header header;
	header.source_port=Sock.addr.port;
	header.dest_port=mic_sock;
	header.seq_num=0;
	header.ack_num=0;
	header.syn=0;
	header.ack=0;
	header.fin=0;

	struct mic_tcp_payload payload;
	payload.data=mesg;	
	payload.size=mesg_size;
		
	struct mic_tcp_pdu pdu;
	pdu.header=header;
	pdu.payload=payload;
	
	struct mic_tcp_sock_addr addrdest;
	addrdest.ip_addr="127.0.0.1";
	addrdest.ip_addr_size=sizeof("127.0.0.1");
	addrdest.port=9000;

		
	return IP_send(pdu,addrdest);
/* -------------------------------------------------------------------*/
}

/*
 * Permet à l’application réceptrice de réclamer la récupération d’une donnée 
 * stockée dans les buffers de réception du socket
 * Retourne le nombre d’octets lu ou bien -1 en cas d’erreur
 * NB : cette fonction fait appel à la fonction app_buffer_get() 
 */
int mic_tcp_recv (int socket, char* mesg, int max_mesg_size)
{
    printf("[MIC-TCP] Appel de la fonction: "); printf(__FUNCTION__); printf("\n");
/* -----------------------Partie Perso -----------------------------------*/
	/*if (socket =! (Sock.fd))
	{
		return -1;        // On vérifie que le socket existe et a la bonne adresse
	}*/

	int retour = -1;

	struct mic_tcp_payload payload;
	payload.size=max_mesg_size;	
	// malloc sur payload data
	payload.data=malloc(payload.size*sizeof(char));

	retour=app_buffer_get(payload);       // On recup le message dans le buffer
	strcpy(mesg,payload.data);			  // On met le message récupéré dans mesg	
	return retour;
/* -------------------------------------------------------------------*/
}

/*
 * Permet de réclamer la destruction d’un socket. 
 * Engendre la fermeture de la connexion suivant le modèle de TCP. 
 * Retourne 0 si tout se passe bien et -1 en cas d'erreur
 */
int mic_tcp_close (int socket)
{
    printf("[MIC-TCP] Appel de la fonction :  "); printf(__FUNCTION__); printf("\n");
    return -1;
}

/*
 * Permet de traiter un PDU MIC-TCP reçu (mise à jour des numéros de séquence
 * et d'acquittement, etc.) puis d’insère les données utiles du PDU dans
 * le buffer de réception du socket. Cette fonction utilise la fonction
 * app_buffer_put(). Elle est appelée par initialize_components()
 */

void process_received_PDU(mic_tcp_pdu pdu, mic_tcp_sock_addr addr)
{
    printf("[MIC-TCP] Appel de la fonction: "); printf(__FUNCTION__); printf("\n");
/* --------------------------------Partie Perso ---------------------------*/	

	app_buffer_put(pdu.payload);
/* ------------------------------------------------------------------------*/

}
