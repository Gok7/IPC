#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#include <fcntl.h>

char ch[10];

main ()
{
  int desc;
   
  printf ("\t\tdebut du programme\n\n");  
  desc = open("./toto",O_RDWR,0);
  if (desc ==-1)
    {
      printf ("erreur a la creation du fichier !!");
      exit(2);
    }
  if(fork()>0)
    {
      /*fils*/
           printf( "\t\t debut du fils \n");
	   printf(" j ecris ab \n");
           write( desc,"ab",2);
	   sleep(1);
            
	   read(desc,ch,2);
	   printf("chaine lue par le fils : %s\n",ch);
	   printf ("fin du fils \n");
    }        
   
    else
      { 
            printf( "\t\t debut du pere \n");
	    sleep(3);
  read(desc,ch,2);
 printf("chaine lue par le pere : %s\n",ch);
 printf ("j ecris xy\n");
           write( desc,"xy",2);
	   
	 
	  
	    printf ("fin du pere \n");
    }
}

  


