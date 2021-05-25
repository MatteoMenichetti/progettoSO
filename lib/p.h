#include "../lib/ipc.h"

#define delim ','
#define ENABLE "FALLIMENTO"

#define INIT_ERR srand(time(NULL))
#define ERR rand() % (10) + 1

void splitP1(char *, int);
void splitP2(char *, int);

int sum(char *);

void p1(int, int);

void p2(int, int );

void p3(int, int);