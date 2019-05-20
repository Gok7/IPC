#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include  <fcntl.h>
#include <string.h>
main()
{
  mode_t mode;
  int p;
  char mess[25];
  mode = S_IRUSR | S_IWUSR | S_IRGRP;
  if (mkfifo("fifo1",mode)==-1)
    perror("creation fifo1");
  else 
    printf ("fifo1 cree\n");
   if (mkfifo("fifo2",mode)==-1)
     perror("creation fifo2");
   else 
     printf ("fifo2 cree\n");
}



	

