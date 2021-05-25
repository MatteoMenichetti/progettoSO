#include "../lib/ipc.h"

#define delim ((const char*)',')
#define ENABLE "FALLIMENTO"

#define INIT_ERR srand(time(NULL))

void splitP1(char *, int);

void splitP2(char *, int);

int sum(char *);

void p1(int);

void p2(int);

void p3(int);