#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int sem_id;
key_t cle;
struct sembuf st_sembuf;
struct semid_ds st_semid;


main(int argc, char* argv[])
{
 int compteur;
 
 if(argc!=2)
 {
   fprintf(stderr,"\t syntaxe: fils_etoile_sem[num cle])");
   exit(2);
 }
 
 cle=atoi(argv[1]);
 sem_id=semget(cle,1,0);
 printf("\tFils_etoile: sem_id=%d cle %d\n",sem_id,cle);
 
 if(sem_id==-1)
 {
   perror("semget");
   exit(2);
 }
 
 printf("\tFils_etoile P(S)\n");
 st_sembuf.sem_num=0;     //selectionne le seul semaphore, num du semaphore
 st_sembuf.sem_op=-1;     //P(S), operation sur le semaphore
 st_sembuf.sem_flg=0;     //flag
 
 semop(sem_id,&st_sembuf,1);      //valide operation (prise de la ressource)
 printf("\tFils_etoile: semaphore ok\n");
 
 for(compteur=0;compteur<5;compteur++)
 {
    printf("\t *\n");
    sleep(1);
 }
 
 printf("\t Fils_etoile V(S)\n");
 st_sembuf.sem_num=0;  
 st_sembuf.sem_flg=0;
 semop(sem_id,&st_sembuf,1);   //valide operation(liberation de la ressource
 
}