#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define PIPEADDR "pipeP1"
#define SOCKADDR "socketP2"
#define FILEADDR "fileP3"
#define PIPEDP1 "pipeDP1"
#define PIPEDP2 "pipeDP2"
#define PIPEDP3 "pipeDP3"
#define DEFAULT 0

void inititializationPIPE();