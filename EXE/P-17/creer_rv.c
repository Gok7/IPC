#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

main(int argc, char* argv[])
{
  int semid;
  int val_init_sem;
  int i;
  key_t cle;
  
  
  if (argc !=3)
    {
      fprintf (stderr,"Syntaxe : creer_rv [nun cle] [nb process])\n");
      exit(2);
    }    
  cle = atoi(argv[1]); //met dans clé le 1er parametre dans ligne de commande (0) 
  val_init_sem = atoi(argv[2]); //met dans val_init_sem le  2eme para donne en ligne de commande 3
  printf ("cle : %d   val_init_sem = %d\n",cle,val_init_sem);

 semid = semget(cle,1,IPC_CREAT|0666); //obtien la nouvelle valeur de l'ensemble des semaphores
 if(semid == -1)
    {
   perror("semget");
      exit(2);
    }
 if ( semctl(semid,0,SETVAL,val_init_sem)==-1) //effectue l'operation de controle
    {
      perror("semctl");
      exit(2);
    } 
 printf ("creation semaphore reussie :semid = %d \n",semid);
}




