#include <stdio.h>
#include <signal.h>
#define NMAX 3

 struct sigaction action;
 int nb_quit,nb_int;
void hand(int sig)
{
 switch(sig)
   {
   case SIGINT:
      printf ("nb_int = %d\n",++nb_int);
      if(nb_int==NMAX) exit(SIGINT);
      break;
   case SIGQUIT:
      printf ("nb_quit = %d\n",++nb_quit);
      if(nb_quit==NMAX) exit(SIGQUIT);
      break;
   default:
      printf("signal non pris en compte\n");
      exit (-1);			  
   }
}


main()
{
 action.sa_handler=hand;
 sigaction(SIGQUIT,&action,NULL);
 sigaction(SIGINT,&action,NULL);
 while(1)  sleep(1);
}





























































































