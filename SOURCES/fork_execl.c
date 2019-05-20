#include <stdio.h>
#include <sys/wait.h>

main (argc,argv)
int argc;
char * argv[];
{
  int status;
   printf (" je suis le pere PID : %d\n",getpid());
  printf (" je fork le fils  \n");

  switch (fork())
    {
   
    case 0: execl("/home/didier/SOURCE_C/EXE/fils_execl","titi","toto",NULL);
            exit(0);
    case -1: 
           printf (" erreur de fork\n");     
	   exit(0);
    default :
           sleep(10);
           printf (" pere attend fin fils %d\n",waitpid(-1,&status,WNOHANG));
    }
  printf (" fin du pere\n");
}
  













