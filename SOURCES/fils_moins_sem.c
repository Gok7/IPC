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
   int i;
   if (argc !=2)
    {
      fprintf (stderr,"\t\tsyntaxe : fils_moins_sem [ nun cle])");
      exit(2);
    }

  cle = atoi(argv[1]);
  semid = semget(cle,1,0);
  printf ("\t\tfils moins : semid = %d  cle %d \n",semid,cle);
 if(semid == -1)
    {
   perror("semget");
      exit(2);
    }
 printf ("\t\tfils moins P(S)\n");
 st_sembuf.sem_num =0;                     // selectionne le  seul semaphore
 st_sembuf.sem_op = -1;                    // P(S)
 st_sembuf.sem_flg = 0;
 semop(semid,&st_sembuf,1);                // valide operation
  printf ("fils moins : semaphore ok\n");
  for (i=0;i<5;i++)
    {
          printf ("\t\t -\n ");      
           sleep(1 );                            
    }
 printf ("\t\tfils moins V(S)\n");
 st_sembuf.sem_num =0;                     // selectionne le  seul semaphore
 st_sembuf.sem_op = 1;                    // V(S)
 st_sembuf.sem_flg = 0;
 semop(semid,&st_sembuf,1); 
}




