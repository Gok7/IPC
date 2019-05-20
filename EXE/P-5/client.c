#include "env_mes.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

main(int argc,char*argv[])
{
    int msgid;
    int index;
    key_t cle;
    struct requete req;
    struct reponse rep;
    
    printf("argc: %d\n",argc);
    
    for(index=0;index<argc;index++)
      printf("argv[%d]: %s\n",index,argv[index]);
    
    cle=ftok(argv[1],'o');
    if(cle==-1)
    {
	fprintf(stderr,"Erreur ftok\n");
	exit(2);
    }
    
    msgid=msgget(cle,0);
    if(msgid==-1)
    {
	perror("msgget");
	exit(3);
    }
    
    srand(time(NULL));
    req.signature = getpid();
    req.type=1;
    req.question=rand()%N_MAX;
    printf("Envoi de la question: %d de %d\n",req.question,req.signature);
    
    if(msgsnd(msgid,&req,2*sizeof(int),0) ==-1)
    {
	perror("msgsnd");
	exit(3);
    }
      
      
      if(msgrcv(msgid,&rep,sizeof(int)*req.question,(long)getpid(),0) ==-1)
      {
	  perror("msgrcv");
	  exit(2);
      }
   
    printf("Reponse recue\n");
    
    for(index=0;index<req.question;index++)
      printf("%d",rep.tab[index]);
  
}