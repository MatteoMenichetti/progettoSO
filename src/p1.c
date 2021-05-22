#include "../lib/p.h"

void connecting(int csfd) {
    struct sockaddr_un sockServer;
    strcpy(sockServer.sun_path, SOCKADDR);
    sockServer.sun_family = AF_UNIX;
    while ((connect(csfd, (struct sockaddr *) &sockServer, sizeof(sockServer))) == -1) {
        perror("client: connect");
        sleep(1);
    }
}

void p1(int modality, int sfd) {
    int pfd = open(PIPEADDR, O_RDONLY);
    char buff[100];
    while (0 == 0) {
        read(pfd, buff, 100);
        printf("P1: legge = %s\n", buff);
        connecting(sfd);
        split(buff);
    }
}

char *split(char *buff) {
    char *token = strtok(buff, delim);
    do {
        printf("token = %s ", token);
        int s=sum(token, 0);
    } while ((token = strtok(NULL, delim)) != NULL);
    return NULL;
}