#include "common.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PIPEPATH "../tmp/pipeP1"
#define SOCKPATH "../tmp/socketP2"
#define FILEPATH "../tmp/fileP3"
#define PIPEDP1PATH "../tmp/pipeDP1"
#define PIPEDP2PATH "../tmp/pipeDP2"
#define PIPEDP3PATH "../tmp/pipeDP3"
#define DEFAULT 0
#define P1 0
#define P2 1
#define P3 2
#define PERMISSIONPIPE 0777

void createPIPE(char*pipe);

int openPIPE(char[], int);