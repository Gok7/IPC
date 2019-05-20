#include <stdio.h>
#include <signal.h>

 sigset_t ens;
 struct sigaction action;

void hand(int sig)
{
  int i;
  printf("signal recu : %d\n",sig);
 sigprocmask(SIG_BLOCK,NULL,&ens);
 printf("signaux  bloques :");
 for (i=1;i<NSIG;i++)
   if (sigismember(&ens,i))
       printf ("%d ",i);
  printf ("\n"); 
 if (sig ==SIGINT)
   {
         action.sa_handler=SIG_DFL;
         sigaction(SIGINT,&action,NULL);
   }  
}

main()
{
 action.sa_handler=hand;
 sigemptyset(&action.sa_mask);
 sigaction(SIGQUIT,&action,NULL);
 sigaddset(&action.sa_mask,SIGQUIT);
 sigaction(SIGINT,&action,NULL);
 while(1)  sleep(1);
}





























































































