#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <stdlib.h>

main(int argc,char* argv[])
{
  struct shmid_ds buf;  //entrée dans la table des segments de mémoire partagé
  int shmid;
  int ret;
  key_t cle;
  int index;
  
  
  int* paddr_rdwr;  //permet de stocker l'adresse d'attachement du segment de memoire partagé
  int* paddr_rdonly; 
  
  if (argc !=2)
    {
      fprintf (stderr,"syntaxe : init_shm [ nun cle])");
      exit(2);
    }
    
  cle = atoi(argv[1]);
  shmid = shmget(cle,256 * sizeof(int),IPC_CREAT|0666);  //renvois l'id du segment de mémoire partagé
                              // creation d'un segment de taille sizeof(int) grâce à IPC_CREAT + droit pour manipuler
  if (shmid ==-1)
 {
   fprintf (stderr," erreur de semget");
   exit(2);
 }
 
  printf ("Creation du segment  ok : shmid= %d \n",shmid);
  
  shmctl(shmid,IPC_STAT,&buf);//réalise opération de controle d'un seg de mem partagée, rentre info dans structure
        //id seg partagé,rempli la structure pointé par &buf avec info relative au segment shmid
  
  printf (" ID utilisateur : %d \n",buf.shm_perm.uid);  //affiche info de la structure shmid_ds
  printf (" Taille du segment : %d\n",buf.shm_segsz);  //idem
  
  
  paddr_rdwr = (int*)shmat(shmid,NULL,0); //attache segment de memoire partagé identifié par shmid au segment de données du process appelant
  //retourne adresse attachement du seg mem partagé, NULL permet que l'adresse soit choisie par le systeme
 
  if (paddr_rdwr == NULL)
 {
   fprintf (stderr," erreur d'attachement en lecture ecriture ");
   exit(3);
 }
 
  printf (" Attachement en lecture ecriture a l'adesse %x \n",paddr_rdwr);
  paddr_rdonly =(int*) shmat(shmid,NULL,SHM_RDONLY); //attachement en lecture ecriture
  
  if (paddr_rdonly == NULL)
 {
   fprintf (stderr," erreur d'attachement en lecture seule ");
   exit(4);
 }
 
  printf (" Attachement en lecture seule a l'adesse %x \n",paddr_rdonly);
  sleep(5);
  printf ("Ecriture dans le segment par paddr_rdwr \n"); 
 
  for (index =0 ;index<256 ; index++)
  {
    paddr_rdwr[index]=index;
  }
   
  printf ("Lecture  dans le segment par paddr_rdonly \n"); 
  
  for (index = 0 ;index<256 ; index++)
  {
    printf ("%d, ", paddr_rdonly[index]);
  }
   
  shmdt(paddr_rdwr);
  shmdt(paddr_rdonly);
  sleep (5);
  shmctl(shmid,IPC_RMID,0);
 }


