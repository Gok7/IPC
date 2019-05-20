#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>

struct sigaction action;
int fils_mort;

void hand(int sig)
{
  pid_t pid;
  int status;
  
  fils_mort++;
  pid=waitpid(-1,&status,0); //suspend exécutution process appellant jusqu'a ce que le fils est changé d'état
              //attent fin n'importe lequel process fils
              //renvoi le pid du fils qui a changé d'état
              //& status non nul enregistre info sur etat dans status qui est pointé
  printf("\t Fin du processus %d\n",pid);
}


main(argc,argv)
int argc;
char* argv[];
{
    int status, id;
    
    printf("\t Je suis le pere PID: %d\n",getpid());
    fils_mort=0;
    action.sa_handler=hand; //sa_handler indique l'action effectué a la reception du signal, ici fonction hand
    sigaction(SIGCHLD,&action,NULL); //a la reception signal SIGCHILD modi de l'action du processus
    printf("\t Pere: fork de fils etoile\n\n");
    
    switch(id=fork())
    {
      case 0:
	execl("/home/iris/IPC/EXE/fils_etoile",NULL);  //remplace l'image memoire du process en cours par un nouveau
        exit(0);
      
      case -1:
	printf("Erreur de fork\n");
	exit(0);
	
      default:
      printf("\t Fils etoile=id %d\n",id);
      
    }
    
    printf("\t Pere: fork de fils_moins\n");
    
    switch(id=fork())
    {
      case 0:
	execl("/home/iris/IPC/EXE/fils_moins",NULL);
        exit(0);
      
      case -1:
	printf("Erreur de fork\n");
	exit(0);
	
      default:
      printf("\t Fils moins=id %d\n",id);
    }
    
    while(fils_mort!=2);
    printf("\t Fin du pere");
}
  
