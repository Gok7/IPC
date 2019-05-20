#include "srv_cli_msg.h"
int msgid;
void hand(int sig)
{ 
  fprintf (stderr,"Fin du serveur\n");
  msgctl(msgid,IPC_RMID,NULL);
  exit(0);
}

main(int argc,char **argv)
{
  key_t cle;
  struct sigaction action;
  struct requete req;
  struct reponse rep;
  int sig,ind;
  printf ("argc :%d\n",argc);
   for (ind=0;ind<argc;ind++)
       printf ("argv[%d] : %s\n",ind,argv[ind]);
  cle = ftok(argv[0],'0');
  if (cle == -1)
    {
      fprintf(stderr,"erreur de ftok\n");
      exit(2);
    }
  msgid = msgget(cle,IPC_CREAT|IPC_EXCL|0666);
  if (msgid == -1)
    {
      perror("msgget");
      exit(3);
    }
  srand(time(NULL));
  while (1)
    {
      if(msgrcv(msgid,&req,2*sizeof(int),1L,0)==-1)
	{
	  perror("msgrcv");
	}
      else
	{  
	  printf ("Question : %d de %d\n",req.question,req.signature);
	  rep.type = req.signature;
	  for(ind=0;ind<req.question;ind++)
               rep.tab[ind]=rand()%NMAX;
          if(msgsnd(msgid,&rep,sizeof(int)*req.question,0)==-1)
	    perror("msgsnd");
	  else
	    printf ("reponse envoyee\n");
	}
    }
}




