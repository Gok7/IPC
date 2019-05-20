#include <stdio.h>
#include <unistd.h>

int g=1000;
main ()
{
  int l=500;
  printf ("\t\tdebut du programme\n\n");
  printf(" dans pere : adressede g  %ud  adresse de l \n",&g,&l);
  printf(" 1 : dans pere g= %d        l=%d \n",g,l);
 switch(fork())
    {
    case -1:   perror ("fork");
               exit(2);
    case 0:      /*fils*/
               printf( "\t\t debut du fils \n");
               printf(" dans pere : adressede g  %ud  adresse de l \n",&g,&l);
	       printf(" 2 : dans fils g= %d        l=%d \n",g,l);
               l=l*2;  g=g*2; 
	       printf(" 3 : dans fils g*2= %d        l*2=%d \n",g,l);
	       sleep(3);
	       printf(" 6 : dans fils g*2= %d        l*2=%d \n",g,l); 
	       exit(0);
               printf ("fin du fils \n");
    default:       
               printf( "\t\t debut du pere \n");
	       sleep(2);
	       printf(" 4 : dans pere g= %d        l=%d \n",g,l);
	       l=l*3;  g=g*3; 
	       printf(" 5 : dans pere g*3= %d        l*3=%d \n",g,l);
	       sleep(2);
	       printf ("fin du pere \n");
	       exit(0);
    }
}

  



