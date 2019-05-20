#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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
  printf ("fils 1 ID = %d\n",getpid());
  sleep(10);
  printf (" fin du fils 1 ID = %d\n",getpid());
 exit(1);
}

void f2(void)
{
  printf ("fils 2 ID = %d\n",getpid());
  sleep(20);
  printf (" fin du fils 2 ID = %d\n",getpid());
 exit(2);
}


main ()
{
    int nproc,rep;
    int status,ind,pid;
  

    tab_fonc[0]=f1;
    tab_fonc[1] = f2;
    nproc =2;
    printf ("debut :pere ID : %d  fork des deux fils\n",getpid());
    rep = forkn(tab_fonc,nproc,tab_pid);
    /*  for (ind=0;ind<2;ind++)
           printf ("fils %d: pid %d\n",ind,tab_pid[ind]);
    */
   do
   {
       printf ("pere attend \n");   
       pid = waitpid(-1,&status,WUNTRACED);
       printf (" apres wait pid = %d  status = %d \n",pid,WEXITSTATUS(status));
    }while (pid !=-1);
    sleep(10);
    printf (" fin du pere \n");  
    
}

  



