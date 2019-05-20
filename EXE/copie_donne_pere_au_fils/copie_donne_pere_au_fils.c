#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int globale=1000;

main(){
 
  int Locale=500;
  printf("\t\tDebut du programme\n\n");
  printf("Dans le pere: adresse de globale: %ud;  adresse de locale %ud\n",&globale,&locale);
  printf("locale: dans le pere g= %d,   local=%d\n",globale,locale);
  
  switch(fork()){
    
    case -1:
      perror("fork");
      exit(2);
  
    case 0:   //fils
      printf("\t\tDebut du fils\n");
      printf("Dans le pere: adresse de globale: %ud;  adresse de locale %ud\n",&globale,&locale);
      printf("2: dans fils globale=%d;   locale=%d\n",globale,locale);
      locale=locale*2;
      globale=globale*2;
      printf("3: Dans fils g*2=%d,      locale*2=%d\n", globale,locale);
      sleep(3);
      printf("6: Dans fils g*2=%d,      locale*2=%d\n", globale,locale);
      exit(0);
      printf("Fin du fils\n");
}