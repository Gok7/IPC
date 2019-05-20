#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>

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

main (argc,argv)
int argc;
char * argv[];
{
  int status,id;
   printf ("\t je suis le pere PID : %d\n",getpid());
   fils_mort =0;
  action.sa_handler = hand;
  sigaction(SIGCHLD,&action,NULL);


 printf("\t pere : fork de fils etoile\n");
  switch (id=fork())
    {
   
    case 0: execl("/home/didier/EXE/fils_eto",NULL);
             
            exit(0);
    case -1: 
           printf (" erreur de fork\n");     
	   exit(0);
 default :
           printf ("\t fils etoile = id %d\n",id);
    }
   printf("\t pere : fork de fils moins\n");
switch (id=fork())
    {
   
    case 0: execl("/home/didier/EXE/fils_moins",NULL);
             
            exit(0);
    case -1: 
           printf (" erreur de fork\n");     
	   exit(0);
 default :
           printf ("\t fils moins = id %d\n",id);
    }
   while (fils_mort !=2);
   printf ("\t fin du pere\n");
}
  













