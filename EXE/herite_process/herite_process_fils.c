#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/times.h>

char bufer[1024];
struct tms temps;

main(){


int u_id,eu_id,g_id,eg_id;
int compteur;
   
  printf("\t Debut du programme\n\n");
  
  for(compteur=0; compteur<100000000;compteur++);   //pour consommer du temps CPU
    
      if(fork() == 0){    //fils
	  printf("Debut du fils.\n\n");
	  u_id = getuid();  //retourne l'id reel du fils
	  eu_id = geteuid();  //retourne l'id effectif du fils
	  g_id = getgid();   //retourne l'id du processus
	  eg_id = getegid();
	  
	  printf("Je suis le fils: u_id=%d,    eu_id=%d;   g_id=%d;   eg_id=%d\n", u_id,eu_id,g_id,eg_id);
	  getcwd(bufer,1024);   // permet d'obtenir le repertoire courant
	  printf("Repertoire de travail: %s\n",bufer);
	  times(&temps);
	  printf("Temps ecoule en mode utilisateur: %d\n", temps.tms_utime);
	  printf("Temps ecoule en mode systeme: %d\n",temps.tms_stime);
	  printf("Fin du fils\n\n");
	  
      }else
      {              //père
      
	printf("\t\t Debut du père\n");
	sleep(5);            //attend l'execution du fils
	u_id = getuid();  //retourne l'id reel du fils
	eu_id = geteuid();  //retourne l'id effectif du fils
	g_id = getgid();   //retourne l'id du processus
	eg_id = getegid();
	  
	printf("Je suis le pere: u_id=%d,    eu_id=%d;   g_id=%d;   eg_id=%d\n", u_id,eu_id,g_id,eg_id);
	getcwd(bufer,1024);    // permet d'obtenir le repertoire courant
	printf("Repertoire de travail: %s\n",bufer);
	times(&temps);
	printf("Temps ecoule en mode utilisateur: %d", temps.tms_utime);
	printf("Temps ecoule en mode systeme: %d\n",temps.tms_stime);
	printf("Fin du pere\n\n");
    }
}
