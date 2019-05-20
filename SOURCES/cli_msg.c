#include "srv_cli_msg.h"

main(int argc,char *argv[])
{
  int msgid,ind;
  key_t cle;
  //  struct sigaction action;
  struct requete req;
  struct reponse rep;
  printf ("argc %d\n",argc);
for (ind =0;ind<argc;ind++)
  printf ("argv[%d] : %s\n",ind ,argv[ind]);
  cle = ftok(argv[1],'0');
  if (cle == -1)
    {
      fprintf(stderr,"erreur de ftok\n");
      exit(2);
    }
  msgid = msgget(cle,0);
  if (msgid == -1)
    {
      perror("msgget");
      exit(3);
    }
  srand(time(NULL));
  req.signature =getpid();
  req.type=1;
  req.question = rand()%NMAX;
  printf ("Envoi de la question : %d de %d\n",req.question,req.signature);
  if (msgsnd(msgid,&req,2*sizeof(int),0)==-1)
    {
       perror("msgsnd");
       exit(3);
    }
  if (msgrcv(msgid,&rep,sizeof(int)*req.question,(long)getpid(),0)==-1)
    {
      perror("msgrcv");
      exit(2);
    }
  printf ("reponse recue\n");
  for(ind=0;ind<req.question;ind++)
    printf ("%d ",rep.tab[ind]);

}
