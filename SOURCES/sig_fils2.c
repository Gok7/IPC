#include <stdio.h>
#include <signal.h>
#include <unistd.h>

 struct sigaction action;
 int nb_recu;
 int nb_envoye;
 int  pid_fils;
void hand_pere(int sig)
{
 if (sig==SIGUSR1)
  	nb_recu++;
 else
   {
     printf ("nombre de signaux recus : %d \n",nb_recu);
     exit(0);
   }
}

void hand_fils(int sig)
{
 if (sig==SIGUSR1)
  	nb_envoye++;
 else
   {
     printf ("nombre de signaux envoye : %d \n",nb_envoye);
     exit(0);
   }
}

main()
{
 sigset_t ens;
 sigemptyset(&ens);
 sigaddset(&ens,SIGUSR1);
 sigprocmask(SIG_BLOCK,&ens,NULL);  // blocage de SIGUSR1
 sigemptyset(&ens); 
 action.sa_handler=hand_pere;
 sigaction(SIGUSR1,&action,NULL);
 sigaction(SIGINT,&action,NULL);
 sigprocmask(SIG_BLOCK,&ens,NULL);
 if ((pid_fils=fork())==0)
 {
  int i;
 action.sa_handler=hand_fils;
 sigaction(SIGUSR1,&action,NULL);
 sigaction(SIGINT,&action,NULL);
  for (i=0;i<20000;i++)  
    {       
       kill (getppid(),SIGUSR1);
       sigsuspend(&ens);
    }
  printf ("fin du fils\n");
  exit(0); 
  }
 while(1)
  {
  sigsuspend(&ens);  
  kill(pid_fils,SIGUSR1);
  }
}






























































































