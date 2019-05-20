#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

main(){


int id_fork,pere_id,fils_id,mon_pere;
   
  printf("Execution du fork\n");

  switch (id_fork=fork())        //permet de tester les differentes valeurs retournées par fork
    {
    case -1:                     //cas d'erreur
           printf ("Erreur de fork\n");
	   exit(2);
    case 0: 
      fils_id = getpid();   //retourne l'id du fils
      mon_pere = getppid();   //retourne l'id du père
      printf ("Valeur du fork = %d\n",id_fork);
      printf ("Je suis le fils : id = %d   Id pere : %d \n",fils_id,mon_pere);
      printf ("Fin du fils \n");
      exit(0);
   
    default:
            pere_id = getpid();
            mon_pere = getppid();
            printf ("Valeur du fork = %d\n",id_fork);
            printf ("Je suis le pere : id = %d mon pere %d\n",pere_id,mon_pere);
	    printf ("Fin du pere \n");
    }
}