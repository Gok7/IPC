#include <stdio.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#define N_MAX 20

struct
{
    long type;
    int question;
    int signature;
};

struct reponse
{
    long type;
    int tba[N_MAX];
    
};