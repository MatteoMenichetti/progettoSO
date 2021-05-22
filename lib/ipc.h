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
#define PIPEDECISIONADDR "pipeDA"
#define DEFAULT 0

int init();