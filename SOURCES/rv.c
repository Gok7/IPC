#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


int semid;
key_t cle;
struct sembuf st_sembuf;
struct semid_ds st_semid;

main(int argc, char* argv[])

{
   int i,tps_travail,pid,sem_val;
   if (argc !=3)
    {
      fprintf (stderr,"\t\tsyntaxe : rv [cle] [tps travail])");
      exit(2);
    }
  pid = getpid();
  cle = atoi(argv[1]);
  tps_travail = atoi(argv[2]);
  semid = semget(cle,1,0);

 if(semid == -1)
    {
   perror("semget");
      exit(2);
    }
 printf ("\t rv %d : Je travail \n",pid);
 sleep(tps_travail);
 printf ("\t rv %d : Je suis au rendez ", pid);
 st_sembuf.sem_num =0;                     // selectionne le  seul semaphore
 st_sembuf.sem_op = -1;                    // P(S)
 st_sembuf.sem_flg = 0;

 semop(semid,&st_sembuf,1);                // valide operation
 sem_val = semctl(semid,0,GETVAL,0);
 printf ( "valeur du semaphore :  %d\n",sem_val); 
 st_sembuf.sem_num =0;                     // selectionne le  seul semaphore
 st_sembuf.sem_op = 0;                    // Z
 st_sembuf.sem_flg = 0;
 semop(semid,&st_sembuf,1); 
 printf (" rv %d : Je reprend le travail\n",pid);

}





