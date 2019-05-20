#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

main(int argc, char* argv[])
{
  int semid,val_init_sem,i;
  key_t cle;
  if (argc !=3)
    {
      fprintf (stderr,"syntaxe : creer_rv [nun cle] [nb process])");
      exit(2);
    }    
  cle = atoi(argv[1]);
  val_init_sem = atoi(argv[2]);
  printf ("cle : %d   val_init_sem = %d\n",cle,val_init_sem);

 semid = semget(cle,1,IPC_CREAT|0666);
 if(semid == -1)
    {
   perror("semget");
      exit(2);
    }
 if ( semctl(semid,0,SETVAL,val_init_sem)==-1)
    {
      perror("semctl");
      exit(2);
    } 
 printf ("creation semaphore reussie :semid = %d \n",semid);
}




