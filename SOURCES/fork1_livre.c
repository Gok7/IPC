#include <stdio.h>
#include <unistd.h>




main (argc,argv)
int argc;
char * argv[];
{
  int idfork,pereid,filsid,monpere;
   
  printf(" execution du fork \n");

  switch (idfork=fork())
    {
    case -1: 
           printf (" erreur de fork\n");
	   exit(2);
    case 0: filsid = getpid();
            monpere = getppid();
          printf ("valeur du fork = %d\n",idfork);
            printf ("je suis le fils : id = %d mon pere : %d \n",filsid,monpere);
	    printf ("fin du fils \n");
            exit(0);
   
    default:
            pereid = getpid();
            monpere = getppid();
            printf ("valeur du fork = %d\n",idfork);
            printf ("je suis le pere : id = %d mon pere %d\n",pereid,monpere);
	     printf ("fin du pere \n");
    }
}

  


