#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>

int semid;
key_t cle;
char ch_cle[10];
struct sembuf st_sembuf;
struct semid_ds st_semid;
struct sigaction action;
int fils_mort;
void hand(int sig)
{
  pid_t pid;
  int status;
  fils_mort ++;
  pid = waitpid(-1,&status,0);
  printf ("\t fin du processus %d\n",pid);
}

main (int argc,char* argv[])

{
  int id;
 if (argc !=2)
    {
      fprintf (stderr,"syntaxe : init_sem [ nun cle])");
      exit(2);
    }

  // mise en place du handler de SIGCHLD
  fils_mort =0;
  action.sa_handler = hand;
  sigaction(SIGCHLD,&action,NULL);

  //mise en place du semaphore 
   printf ("debut du pere \n");
  cle = atoi(argv[1]);
 
  semid = semget(cle,1,IPC_CREAT|0666);
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

  sleep(2);
    printf("\t pere : fork de fils moins\n");
  switch (id = fork())
    {  
    case 0:  
            execl("/home/didier/EXE/fils_moins_sem","sem",argv[1],NULL);              
            exit(0);
    case -1: 
           printf (" erreur de fork\n");     
	   exit(0);
	     default :
           printf ("\t fils moins = id %d\n",id);
	    }
  
    printf("\t pere : fork de fils etoile\n");
switch (id = fork())
    {  
    case 0: execl("/home/didier/EXE/fils_eto_sem","sem",argv[1],NULL);             
            exit(0);
    case -1: 
           printf (" erreur de fork\n");     
	   exit(0);
	    default :
           printf ("\t fils etoile  = id %d\n",id);
	    }
  
//  sleep(12);
   while (fils_mort !=2);
   printf (" fin du pere\n");
   
}
  














