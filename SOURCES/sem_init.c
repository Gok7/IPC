#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


int semid;
key_t cle;
struct sembuf st_sembuf;
struct semid_ds st_semid;
main( int argc,char* argv[])
{
 
 printf ("creation semaphore \n");
  cle =ftok(argv[0],'0');
 if (cle == -1)
   {
     perror("ftok ");
      exit(2);
    }
  semid = semget(cle,1,IPC_CREAT|IPC_EXCL|0666);
 if(semid == -1)
    {
   perror("semget");
      exit(2);
    }
 if ( semctl(semid,0,SETVAL,1)==-1)
    {
      perror("semctl");
      exit(2);
    } 
 printf ("creation semaphore reussie :semid = %d \n",semid);
 semctl(semid,0,IPC_STAT,&st_semid);
 printf (" nbre  de semaphore : %d ",st_semid.sem_nsems);
 


 }








