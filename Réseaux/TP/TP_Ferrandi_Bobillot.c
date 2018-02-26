#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>

void construire_message(char *message, char motif, int lg) {
	int i;
	for (i=0;i<lg;i++) message[i] = motif;
}



void afficher_messagepu(char *message, int lg, int port, int i) {
	printf("PUITS : Reception n°%d (%d) [----%d%s]\n",i+1,lg,i+1,message);
}




void afficher_messagesu(char *message, int lg, int port,int nb_envoi, char* dest, int i) {

	if (i==0)
	{
		printf("SOURCE : lg_message_emis=%d, port=%d, nb_envois=%d, TP=udp\n",lg,port,nb_envoi);
	}
	printf("SOURCE : Envoi n°%d (%d) [----%d%s]\n",i+1,lg,i+1,message);

}




void afficher_messagept(char *message, int lg, int port,int i) {    /* puits tcp */
	printf("PUITS : Reception n°%d (%d) [----%d%s]\n",i+1,lg,i+1,message);
}





void afficher_messagest(char *message, int lg, int port,int nb_envoi, char* dest, int i) {
	if (i==0)
	{
		printf("SOURCE : lg_message_emis=%d, port=%d, nb_envois=%d, TP=tcp \n",lg,port,nb_envoi);
	}
	printf("SOURCE : Envoi n°%d (%d) [----%d%s]\n",i+1,lg,i+1,message);

}


main (int argc, char **argv)
{
	int c;
	extern char *optarg;
	extern int optind;
	int nb_message = 10; /* Nb de messages à envoyer ou à recevoir, par défaut : 10 en émission, infini en réception */
	int lg_mess = 30;
	int source = -1 ; /* 0=puits, 1=source */
	int protocole = 1; /* 0=UDP, 1=TCP */

	int sock;
	int sock_bis;
	int port; 
	struct hostent *hp;	
	struct sockaddr_in adr;
	char *message;
	message=malloc(sizeof(char)*30);
	int a;    					//Variable pour récupérer la sortie des sendto ou recvfrom
	int motif=97; 				//ASCII de 'a'
	int lg_adr = sizeof(adr);	
	int lg_mess_recu;
	int *pt_adr_client;
	struct sockaddr * pt_struct_adr_client;

	while ((c = getopt(argc, argv, "psun:l:")) != -1) {
		switch (c) {
		case 'p':
			if (source == 1) {
				//printf("usage: cmd [-p]\n");
				exit(1);
			}
			source = 0;
			break;

		case 's':
			if (source == 0) {
				//printf("usage: cmd [-s]\n");
				exit(1) ;
			}
			source = 1;
			break;

		case 'u':
			//printf("usage : cmd [-u]\n");
			protocole =0;
			break;
		case 'n':
			nb_message = atoi(optarg);
			break;
		case 'l':
			lg_mess = atoi(optarg);
			break;

		default:
			printf("Erreur : argument non reconnu\n");
			break;
		}
	}

	if (protocole == 0){

		if (source == -1) {
			printf("Erreur :  renseigner au moins un argument parmi : -p -s\n");
			exit(1) ;
		}

		if (source == 1) {
			/* Creer socket local */
			//printf("on est dans le source\n");
			if((sock = socket(AF_INET, SOCK_DGRAM, 0))== -1)
			{
				printf("échec de création du socket\n");
				exit(1);
			}
			/* construire adresse socket auquel il s'adresse */
			port = atoi(argv[argc-1]);
			adr.sin_port = htons(port);
			adr.sin_family = AF_INET;
			if((hp=gethostbyname(argv[argc-2]))==NULL)
			{ 
				printf("erreur gethostbyname\n");
				exit(1);
			}
	
			memcpy((char*)&(adr.sin_addr.s_addr),hp->h_addr,hp->h_length);
			/* sendto*/
			for (int i=0;i<nb_message;i++)
			{
				construire_message(message,(motif+i),lg_mess);
				a=sendto(sock,message,lg_mess,0,&adr,sizeof(struct sockaddr_in));
				afficher_messagesu(message,lg_mess,port,nb_message,atoi(argv[argc-2]),i);
			}			
			//printf("Sortie sendto : %d    Nbr caractères envoyés (-1 si erreur)\n",a);
				 
			
		}
		else
		{
			//printf("on est dans le puits\n");
			/*Creer socket local*/
			if((sock = socket(AF_INET, SOCK_DGRAM, 0))== -1)
			{
				printf("échec de création du socket\n");
				exit(1);
			}
			/* construire adresse socket réception*/
			port = atoi(argv[argc-1]);
			adr.sin_port= htons(port);
			adr.sin_family = AF_INET;
			adr.sin_addr.s_addr=INADDR_ANY;
			/*binder*/
			if (bind(sock, (struct sockaddr *)&adr,sizeof(struct sockaddr)) == -1)
			{
				printf("échec du bind\n");
				exit(1);
			}
			/* receve from */ 	
			int i=0;
			printf("PUITS : lg_message_lu=%d, port=%d, nb_receptions=infini, TP=udp\n",lg_mess,port);
			while(1)
			{		
				lg_mess=recvfrom(sock,message,lg_mess,0,(struct sockaddr*)&adr,&lg_adr);
				afficher_messagepu(message,lg_mess,port,i);
				i++;
			}			
			//printf("Sortie recvfrom : %d    Nbr octets lus (-1 si erreur)\n",a);	
			
			
		}
	}
	else 
	{
		if (source == -1) {
			printf("Erreur :  renseigner au moins un argument parmi : -p -s\n");
			exit(1) ;
		}

		if (source == 1) {
	/* Etablissement connexion Client ----------------------------------------*/
			/* Creer socket local */
		//	printf("on est dans le source\n");
			if((sock = socket(AF_INET, SOCK_STREAM, 0))== -1)
			{
				printf("échec de création du socket\n");
				exit(1);
			}
			/* construire adresse socket auquel il s'adresse */
			port = atoi(argv[argc-1]);
			adr.sin_port = htons(port);
			adr.sin_family = AF_INET;
			if((hp=gethostbyname(argv[argc-2]))==NULL)
			{ 
				printf("erreur gethostbyname\n");
				exit(1);
			}
	
			memcpy((char*)&(adr.sin_addr.s_addr),hp->h_addr,hp->h_length);

			/* Connexion au socket serveur*/

			if((connect(sock,(struct sockaddr *)&adr,sizeof(struct sockaddr)))==-1)
			{
				printf("echec du connect\n");
				exit(1);
			}

			/* Phase de transfert de données */
			for (int i=0;i<nb_message;i++)
			{
				construire_message(message,(motif+i),lg_mess);
				if((a=write(sock,message,lg_mess))<0)
				{
					printf("echec du write\n");
					exit(1);
				}
				afficher_messagest(message,lg_mess,port,nb_message,atoi(argv[argc-2]),i);
			}	
			if(shutdown(sock,2)==-1)
				{
					printf("erreur à la fermeture du socket \n");
				}
	/* ------------------------------------------------------------------*/		
				 
			
		}
		else
		{
	/* Cote serveur de la connexion -------------------------------------*/
			//printf("on est dans le puits\n");
			/*Creer socket local*/
			if((sock = socket(AF_INET, SOCK_STREAM, 0))== -1)
			{
				printf("échec de création du socket\n");
				exit(1);
			}
			/* construire adresse socket réception*/
			port = atoi(argv[argc-1]);
			adr.sin_port= htons(port);
			adr.sin_family = AF_INET;
			adr.sin_addr.s_addr=INADDR_ANY;
			/*binder*/
			if (bind(sock, (struct sockaddr *)&adr,sizeof(struct sockaddr)) == -1)
			{
				printf("échec du bind\n");
				exit(1);
			}	
			/* Mise en etat d'acceptation de toute demande de connexion */
			printf("PUITS : lg_message_lu=%d, port=%d, nb_receptions=infini, TP=tcp\n",lg_mess,port);
			listen(sock,5);
			if((sock_bis = accept(sock,pt_struct_adr_client,pt_adr_client)) == -1)
			{
				printf("échec du accept\n");
				exit(1);
			}
			
			/* Phase de transfert de données */
			for (int i=0;i<nb_message; i++)
			{
				if ((lg_mess= read(sock_bis,message,lg_mess))<0)
				{
					printf("échec du read \n");
					exit(1);
				}
				afficher_messagept(message,lg_mess,port,i);
			}
			if(shutdown(sock_bis,2)==-1)
				{
					printf("erreur à la fermeture du socket bis \n");
				}
			/*if(shutdown(sock,2)==-1)
				{
					printf("erreur à la fermeture du socket \n");
				}*/
			
	/* --------------------------------------------------------------*/			
		}	
	}		
}

