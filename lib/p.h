#include "../lib/ipc.h"
#include <time.h>
#include <sys/wait.h>

#define ERR rand() % (10)
#define delim ","
#define ENABLE "FALLIMENTO"
#define EVENT 0
#define ACTIVE_FAILURE 1

void splitP1(char *, int *);

char *splitP2(char *);

int sum(char *, int);

void p1(int, int);

void p2(int, int);

void p3(int, int);

void errsum(int *, int);