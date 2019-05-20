#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

main()
{
 pid_t pid;
 int status;
  if ((pid=fork())==0)
  {
          while(1) sleep(1);
  }
  sleep(3);
  if (kill(pid,0)==-1)
       printf ("fils %d inexistant\n",pid);
 else
   {
     printf ("envoi du signal SIGUSR1  au processus %d\n",pid);
     kill(pid,SIGUSR1);
   }
 pid =waitpid(pid,&status,0);
 printf ("Status du fils %d :st =  %d,  SIGUSR1 : %d\n",pid,WTERMSIG(status),SIGUSR1);               
}




