#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>


int fils_mort;
int sem_id;
key_t cle;  // creation de la cle
char ch_cle[10];
struct sembuf st_sembuf; //coorespond à une entree dans la table des semaphores accessible par semctl
struct semid_ds st_semid; //correspond à une opération sur les sémaphores
struct sigaction action;

//***************************************************************************************


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

//***************************************************************************************



main(int argc,char* argv[])

{
    int id;
    
    if(argc!=2)
    {
      fprintf(stderr,"Syntaxe: init_sem[num cle])\n");
      exit(2);
    }
    
    //mise en place du handler de SIGCHLD
    fils_mort=0;
    action.sa_handler=hand; //sa_handler indique l'action effectué a la reception du signal, ici fonction hand
    sigaction(SIGCHLD,&action,NULL); //a la reception signal SIGCHILD modi de l'action du processus
  
    //mise en place du semaphore
    printf("Debut du pere\n");
    cle=atoi(argv[1]);
    sem_id=semget(cle,1,IPC_CREAT|0666); //retourne l'identificateur de l'ensemble de sémaphores associé à la valeur cle
                                        //nouvel ensemble est crée avec IPC_CREAT et droit ecriture sur jeu de semaphores
    if(sem_id ==-1)
    {
      perror("Semget");
      exit(2);
    }
    
    if(semctl(sem_id,0,SETVAL,1) ==-1) //operation de controle sur les semaphores indiqué par cmd
    {        //ensemble sem, premiere semaphore,
      perror("Semctl");
      exit(2);
    }
    
    printf("Creation de semaphores reussie. sem_id=%d\n",sem_id);
    sleep(2);
    
    printf("\t Pere: fork de fils moins\n");
    
     switch(id=fork())
    {
      case 0:
	execl("/home/iris/IPC/EXE/P-14/fils_moins_sem","sem",argv[1],NULL); //remplace l'image memoire du process en cours par un nouveau
        exit(0);                                                            //passe ces parametre au fils_etoile_sem
                                                                            //ecrasement du code donc si printf apres il ne s'executera pas
      case -1:
	printf("Erreur de fork\n");
	exit(0);
	
      default:
      printf("\t Fils moins=id %d\n",id);
    }
    
    printf("\tFork de fils etoile\n");
    
    switch(id=fork())
    {
      case 0:
	execl("/home/iris/IPC/EXE/P-14/fils_etoile_sem","sem",argv[1],NULL);  //remplace l'image memoire du process en cours par un nouveau
        exit(0);                                            //passe ces parametre au fils_etoile_sem
                                                       //ecrasement du code donc si printf apres il ne s'executera pas
      case -1:
	printf("Erreur de fork\n");
	exit(0);
	
      default:
      printf("\t Fils etoile=id %d\n",id);
      
    }
    
    //attente de la mort des fils
    while(fils_mort!=2);
    
   //suppression de semaphore
    semctl(sem_id,0,IPC_RMID,0);
    printf("\t Fin du pere");
}
  
