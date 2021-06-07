#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define PIPEADDR "../tmp/pipeP1"
#define SOCKADDR "../tmp/socketP2"
#define FILEADDR "../tmp/fileP3"
#define PIPEDP1 "../tmp/pipeDP1"
#define PIPEDP2 "../tmp/pipeDP2"
#define PIPEDP3 "../tmp/pipeDP3"
#define DEFAULT 0
#define P1 1
#define P2 2
#define P3 3

void inititializationPIPE();
void openPIPE(int*);