#include "../lib/ipc.h"
#include <time.h>

#define ERR rand() % (10) + 1
#define delim (",")
#define ENABLE "FALLIMENTO"
#define EVENT 0
#define ACTIVE_FAILURE 1

void splitP1(char *, int *, int);

char* splitP2(char *);

int sum(char *, int);

void p1(int);

void p2(int);

void p3(int);

void errsum(int *, int);