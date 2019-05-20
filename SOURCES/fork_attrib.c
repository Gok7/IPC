#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>

char buf[1024];
struct tms temps;

main ()
{
  int uid,euid,gid,egid;
  int i;
  
  printf ("\t\tdebut du programme\n\n");  
  for (i=0;i<100000000;i++);    /* pour consommer du temps CPU */


  if(fork()==0)
    {
      /*fils*/
           printf( "\t\t debut du fils \n");
	   //           for (i=0;i<5000000;i++);
           uid  = getuid();
           euid  = geteuid();
	   gid  = getgid();
	   egid  = getegid();
        
            printf ("je suis le fils : uid = %d euid : %d gid = %d  egid = %d\n",uid,euid,gid,egid);
	    getcwd(buf,1024);
            printf( " Repertoire de travail :%s\n",buf); 
	    times(&temps);
	    printf("Temps ecoule en mode utilisateur :%d\n", temps.tms_utime);
	    printf("Temps ecoule en mode systeme :%d\n", temps.tms_stime);
	    printf ("fin du fils \n");
    }        
   
    else
      { 
            printf( "\t\t debut du pere \n");
            sleep(5);  /*attend l'execution du fils  */
	    uid  = getuid();
	    euid  = geteuid();
	    gid  = getgid();
	    egid  = getegid();
nice(10);
            printf ("je suis le pere : uid = %d euid : %d gid = %d  egid = %d\n",uid,euid,gid,egid);
	    getcwd(buf,1024);
            printf( " Repertoire de travail :%s\n",buf);
          
	    times(&temps);
	    printf("Temps ecoule en mode utilisateur :%d\n", temps.tms_utime);
	    printf("Temps ecoule en mode systeme :%d\n", temps.tms_stime);
	    printf ("fin du pere \n");
    }
}

  


