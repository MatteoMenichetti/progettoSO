#include "../lib/ipc.h"
#include <time.h>

#define ERR rand() % (10) + 1
#define delim ((const char*)',')
#define ENABLE "FALLIMENTO"
#define EVENT 0
#define ACTIVE_FAILURE 1

void splitP1(char *, int, int);

void splitP2(char *, int, int, int, int);

int sum(char *, int);

void p1(int,int);

void p2(int, int);

void p3(int,int);

void errsum(int *, int);