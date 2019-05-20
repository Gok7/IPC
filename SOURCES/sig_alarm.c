#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define TEMPS 5
struct sigaction action;

void hand(int sig)
{
  printf ("\nLa reponse n'est pas arrivee a temps !\n");
  exit(0);
}
main()
{
  int rep;
action.sa_handler = hand;
sigaction(SIGALRM,&action,NULL);
printf ("Saisissez un nombre :");
alarm(TEMPS);
scanf("%d",&rep);
alarm (0);
printf ("Vous avez saisi  :%d\n",rep);
} 



