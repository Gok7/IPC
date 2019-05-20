#include <stdio.h>
#include <signal.h>
#include <unistd.h>

 struct sigaction action;
 int nb_recu=0;
void hand(int sig)
{
 if (sig==SIGUSR1)
  	nb_recu++;
 else
   {
     printf ("nombre de signaux recus : %d \n",nb_recu);
     exit(0);
   }
}


main()
{
 action.sa_handler=hand;
 sigaction(SIGUSR1,&action,NULL);
 sigaction(SIGINT,&action,NULL);
 if (fork()==0)
 {
  int i;
  for (i=0;i<20000;i++)  
       kill (getppid(),SIGUSR1);
  printf ("fin du fils\n");
  exit(0); 
  }
 while(1)  pause();
}





























































































