#include "../lib/ipc.h"
#include <time.h>
#include <sys/wait.h>

#define random_failure rand() % (10) //è necessaria solo una cifra decimale per la probabilita 1/10
#define DELIMITER ","
#define FAILURE "FALLIMENTO"
#define EVENT 0
#define ACTIVE_FAILURE 1

void splitP1(char *, int *);

char *splitP2(char *);

int sum(char *, unsigned long);

void p1(int, int);

void p2(int, int);

void p3(int, int);

void errsum(int *, int);