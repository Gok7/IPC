#include <stdio.h>


main(argc,argv)
int argc ;
char* argv[];
{
  int i;

  printf (" \t je suis le fils_execl PID : %d \n",getpid());
  printf (" fils : j ai recu %d arguments :\n",argc);
  
  for (i=0;i<argc;i++)
          printf ("\t arg %d : %s\n ",i,argv[i]);
     
  sleep(15);
  printf ("fin du fils\n");
  exit(0);
}


