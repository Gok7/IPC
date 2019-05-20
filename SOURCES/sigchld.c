#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_PROC 10
  void (*tab_fonc[MAX_PROC])(void);
  int tab_pid[MAX_PROC];

int forkn(void (*tab_fonc[])(void),int nb_fils,int* tab_id)
{
 static int  pid;
 int i,numfils;
 numfils = 0;
 for (i=0;i<nb_fils;i++)
       switch(pid = fork())
	 {
	 case 0: (*tab_fonc[i])();  exit(0);
         default: if ((tab_pid[i] = pid)>0)
                  numfils++;
         }
  return numfils;
}  

void f1(void)
{
  sleep(5);
  printf (" fin du fils 1 ID = %d\n",getpid());
}

void f2(void)
{
  sleep(2);
  printf (" fin du fils 2 ID = %d\n",getpid());
}

void f3(void)
{
  sleep(7);
  printf (" fin du fils 3 ID = %d\n",getpid());
}
void hand(int sig)
{
  pid_t pid;
  int status;
  pid = waitpid(-1,&status,0);
  printf ("terminaison du processus %d\n",pid);
}

main ()
{
    int nproc,rep;
    int status,ind,pid;
     static struct sigaction action;

    tab_fonc[0]=f1;
    tab_fonc[1] = f2;
    tab_fonc[2]=f3;
    nproc =3;
    action.sa_handler = hand;
    sigaction(SIGCHLD,&action,NULL);  
    rep = forkn(tab_fonc,nproc,tab_pid);
    while(1)
      {
        printf ("je travaille\n");
    sleep(1);
      }  
}

  



