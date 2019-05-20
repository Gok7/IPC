#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

main(int argc,char* argv[])
{
  struct shmid_ds buf;
  int shmid,ret;
  key_t cle;
  int ind;
  int* paddr_rdwr;  int* paddr_rdonly; 
  if (argc !=2)
    {
      fprintf (stderr,"syntaxe : init_shm [ nun cle])");
      exit(2);
    }
  cle = atoi(argv[1]);
  shmid = shmget(cle,256 * sizeof(int),IPC_CREAT|0666);
 if (shmid ==-1)
 {

   fprintf (stderr," erreur de semget");
   exit(2);
 }
  printf ("creation du segment  ok : shmid= %d \n",shmid);
  shmctl(shmid,IPC_STAT,&buf);
  printf (" ID utilisateur : %d \n",buf.shm_perm.uid);
  printf (" Taille du segment : %d\n",buf.shm_segsz);
  paddr_rdwr = (int*)shmat(shmid,NULL,0);
  if (paddr_rdwr == NULL)
 {
   fprintf (stderr," erreur d'attachement en lecture ecriture ");
   exit(3);
 }
  printf (" attachement en lecture ecriture a l'adesse %x \n",paddr_rdwr);
 paddr_rdonly =(int*) shmat(shmid,NULL,SHM_RDONLY);
  if (paddr_rdonly == NULL)
 {
   fprintf (stderr," erreur d'attachement en lecture seule ");
   exit(4);
 }
  printf (" attachement en lecture seule a l'adesse %x \n",paddr_rdonly);
  sleep(5);
 printf ("ecriture dans le segment par paddr_rdwr \n"); 
 for (ind =0 ;ind<256 ; ind++)
   paddr_rdwr[ind]=ind;
 printf ("lecture dans le segment par paddr_rdonly \n"); 
 for (ind = 0 ;ind<256 ; ind++)
   printf ("%d ", paddr_rdonly[ind]);
 shmdt(paddr_rdwr);
 shmdt(paddr_rdonly);
sleep (5);
 shmctl(shmid,IPC_RMID,0);
 }


