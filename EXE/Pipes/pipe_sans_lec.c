#include <stdio.h>
#include <signal.h>

struct sigaction action;  // pour pouvoir accèder aux info

void hand(int sig){
 
  printf("Signal SIGPIPE recu\n");
}


main()
{

    int nb_ecrit;
    int p[2];
    action.sa_handler = hand; //indique l'action affectée au signal,ici fonction hand
    sigaction(SIGPIPE,&action,NULL);  //sert à modifier l'action éffectuer par un processus à la réception du signal
    pipe(p); //creation pipe
    close(p[0]); //ferme la lecture donc on ne peut plus rien écrire
    nb_ecrit=write(p[1],"A",1);
    if(nb_ecrit == -1) perror("Writte");
    else   printf("Nb_ecrit: %d\n", nb_ecrit);
    
}
