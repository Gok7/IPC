#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

int semid;
key_t cle;  // creation de la cle
struct sembuf st_sembuf; //coorespond à une entree dans la table des semaphores accessible par semctl
struct semid_ds st_semid; //correspond à une opération sur les sémaphores




main(int argc, char* argv[])
{
 printf("Creation semaphore\n\n");
 cle = ftok(argv[0],'o');  //converti nom+chemin d'acces ainsi que nom projet en clé IPC
 if(cle==-1)
 {
   perror("Erreur ftok");
   exit(2);
 }
 semid=semget(cle,1,IPC_CREAT|IPC_EXCL|0666); //retourne l'identificateur de l'ensemble des sémaphores associé à la valeur cle.
              //cle, nb de sémaphores dans l'ensemble, option
 if(semid==-1) //cas d'erreur semget
 {
   perror("Erreur semget");
   exit(2);
 }
 
 
 if(semctl(semid,0,SETVAL,1) ==-1) //effectue opération controle par cmd sur ensemble sem
 {      //id sem, 1er sem ensemble,initialisation valeur du sémaphore à arg
   perror("Erreur semctl");//cas d'erreur semctl
   exit(2);
 }
 
 printf("Creation sémaphores réussies: semid: %d\n",semid);
 semctl(semid,0,IPC_STAT,&st_semid);//opération controle ,IPC_STAT copie dans la structure pointée par ast_semid 
                                     //la structure de donné concernant l'ensemble de semaphore
 printf("Nombre de sémaphores: %d\n",st_semid.sem_nsems); 
 
 
}