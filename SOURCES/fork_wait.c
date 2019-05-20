#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
main ()
{
  int pid,status;
     if(fork()==0)
    {    /*fils*/
      printf (" ID pere : %d       ID fils : %d\n",getppid(),getpid()); 
           sleep (5);
           printf( "\t\t fin du fils numero %d \n",getpid());
	   exit(2);
    }
     else 
    {
           printf ("pere attend \n");
            
                 pid = wait(&status);
	   //  pid = waitpid(-1,&status,WUNTRACED);
	  printf (" apres wait pid = %d\n",pid);
	  sleep(10);
	  printf (" fin du pere \n");  
    }
}

  



