#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int p[2];  //créer un pipe P[0] représente le descripteur en lecteur P[1] en écriture
           // retourne -1 en cas d'erreur et 0 pour succès
           
char infos[10];
int statut_r,statut_w;  //sert à stocker attributs de P[0] et P[1]
struct stat noeud_r,noeud_w;  //récupére caracterisques pipe dans struct stat  
           
main ()
{

  if(pipe(p) == -1) {
    
      perror("Creation du pipe\n"); 
      exit(2);
  }
  
 statut_r=fcntl(p[0],F_GETFL);  //retourne les attributs de p[0] grace à F_GETFL 
  
  if(statut_r == -1){  //si lecture pas ok
    
      perror("fcntl lecture");
      exit(2);
  }

  statut_w=fcntl(p[1],F_GETFL);  //retourne les attributs de p[1] grace à F_GETFL 
  
  if(statut_w == -1){ //si ecriture pas ok
    
      perror("fcntl ecriture");
      exit(2);
  }
  
  printf("Attributs du descripteur %d en lecture(p[0]): %d\n",p[0],statut_r);
  printf("Attributs du descripteur %d en ecriture(p[1]): %d\n",p[1],statut_w);
  printf("\n Ecriture\n");
  
  if((write(p[1],"0123456789",10)) ==-1);  //si echec de l'écriture
    read(p[0],infos,5);     //lire les 5 premiers carac dans ch
    
  printf("Je lis dans le pipe: %s\n",infos);
  fstat(p[0],&noeud_r);  //récupére le statut du fichier pointé par le descripteurp[0] 
  fstat(p[1],&noeud_w);  //récupére le statut du fichier pointé par le descripteurp[1] 
  printf("Numero noeud: %d\n", noeud_r.st_ino);
  printf("Numero disque: %d\n",noeud_r.st_dev);
  printf("Nombre de lien physique: %d\n",noeud_r.st_nlink);
  printf("Taille: %d\n",noeud_r.st_size);
  
}


