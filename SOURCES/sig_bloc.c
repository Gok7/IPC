#include <stdio.h>
#include <signal.h>

 int sig;
 sigset_t ens1,ens2,ens3;

main()
{
 sigemptyset(&ens1);
 sigaddset(&ens1,SIGINT);
 sigaddset(&ens1,SIGQUIT);
 sigaddset(&ens1,SIGUSR1);
 sigprocmask(SIG_SETMASK,&ens1,NULL);
 sleep(10);
 sigpending(&ens2);
 printf("signaux pendants bloques :");
 for (sig=1;sig<NSIG;sig++)
   if (sigismember(&ens2,sig))
       printf ("%d ",sig);
  printf ("\n");
 sleep(5);
 sigemptyset(&ens3);
 printf ("deblocage des signaux\n");
 sigprocmask(SIG_SETMASK,&ens3,NULL);
 printf ("FIn du processus");
                
}




