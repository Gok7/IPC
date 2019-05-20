#include "env_mes.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int msgid; //identifiant de la file de msg

void hand(int sig)
{
    fprintf(stderr,"Fin du serveur\n");
    msgctl(msgid,IPC_RMID,NULL); //permet d'acceder aux infos contenues dans l'entrée de la table des files dy sys et modif
    exit(0);                     // IPC_RMID supprime la file de message
  
}


main(int argc,char**argv)
{
    key_t cle;  //déclaration clée
    struct sigaction action;   //servira à modifier l'action effectuée par process à la reception d'un signal spécifique
    struct requete req;
    struct reponse rep;
    int sig,index;
    
    printf("argc: %d\n", argc);  //argc: nb de parametres effectivmentpassée (<1 car nom prog)
    
    for(index=0;index<argc;index++)
      printf("argv[%d]: %s\n",index,argv[index]);  //argv[] contient les parametres passé dans ligne de commande
      //affiche nom du programme
      
    cle=ftok(argv[0],'o'); //permet de générer une clé , (ref objet,num cle unique)
    
    if(cle ==-1)  //en cas d'erreur
    {
      fprintf(stderr,"Erreur de ftok\n");
      exit(2);
    }
    
    msgid=msgget(cle,IPC_CREAT | IPC_EXCL |0666); //retourne identificateur de la file de mesg associé à la cle
            
    if(msgid ==-1) //en cas d'erreur
    {
     perror("Erreur msgget");
     exit(3);
    }
    
    srand(time(NULL));
    
    while(1)
    {
	if(msgrcv(msgid,&req,2*sizeof(int),1L,0) ==-1){ //permet au process d'extraire le msg de la file msgid
	      // id file, adresse,zone memoire susceptible de recevoir le mesg, taille msg,type
	  perror("Erreur msgrcv");
	}
	else
	{
	  printf("Question: %d de %d\n",req.question, req.signature);
	  rep.type = req.signature;  //copie de signature dans reponse
	  
	  for(index=0;index<req.question;index++)
	    rep.tab[index]=rand()%N_MAX;
	  
	  if(msgsnd(msgid,&rep,sizeof(int)*req.question,0) ==-1) //envoie dans la file msgid le msg pointé par &rep 
	    perror("Erreur msgsnd");
	  else
	    printf("Reponse envoyee\n");
	  
	}
    }

}



