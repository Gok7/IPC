#include <stdio.h>
#include <unistd.h>

main ()
{  
     printf (" debut du pere : ID %d\n",getpid());
     if(fork()==0)
    {    /*fils*/
          sleep (5);  
           printf( "\t\t fin du fils ID %d \n",getpid());
	   exit(2);
    }
     else
    {
      sleep(20);
      printf ("fin du pere\n");
    }
}

  



