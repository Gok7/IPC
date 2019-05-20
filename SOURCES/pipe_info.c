#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int p[2];
char ch[10];
int status_r,status_w;
struct stat noeud_r,noeud_w;

main()
{
  if (pipe(p) == -1) 
   {
     perror("Creation du pipe");
     exit(2);
   }
   status_r = fcntl(p[0],F_GETFL);   /* retourne les attributs de p[0] */ 
   if (status_r == -1) 
   {
     perror(" fcntl lecture");
     exit(2);
   }
   status_w = fcntl(p[1],F_GETFL);   /* retourne les attributs de p[1] */ 
   if (status_w == -1) 
   {
     perror(" fcntl ecriture");
     exit(2);
   }
   printf ("Attributs du desc %d en lecture (p[0]) : %d\n",p[0],status_r);
   printf ("Attributs du desc %d en ecriture (p[1]) : %d\n",p[1],status_w);
   printf ("ecriture\n");   
 if ((write (p[1], "0123456789",10))==-1);
       read (p[0],ch,5);
   printf(" Je lis dans le pipe : %s\n",ch);
   fstat(p[0],&noeud_r);
   fstat(p[1],&noeud_w);
   printf ("numero noeud : %d\n",noeud_r.st_ino);
   printf ("numero disque : %d\n",noeud_r.st_dev);
   printf ("nbr lien physique : %d\n",noeud_r.st_nlink);
   printf ("taille : %d\n",noeud_r.st_size); 
}  



	
