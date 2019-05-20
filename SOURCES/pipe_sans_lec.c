#include <stdio.h>
#include <signal.h>

struct sigaction action;

void hand(int sig)
{
  printf ("signal SIGPIPE recu\n");
}
 

main()
{
   int nb_ecrit;
   int p[2];
   action.sa_handler = hand;
   sigaction (SIGPIPE,&action,NULL);
   pipe(p);
   close (p[0]);
   nb_ecrit = write(p[1],"A",1);
   if (nb_ecrit == -1) 
          perror ("Write");
   else 
      printf ( " nb_ecrit : %d\n",nb_ecrit);
}  



	
