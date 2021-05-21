#include "../lib/p.h"

void connecting(int csfd){
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

    char strWrite[100], strRead[100];

    int nrchar = read(0, strWrite, sizeof(strWrite));
    strWrite[nrchar - 1] = '\0';
    printf("client: strWrite = %s\n", strWrite);
    write(sfd, strWrite, strlen(strWrite));
    fsync(sfd);
    printf("client: scritto, leggo\n");
    read(sfd, strRead, strlen(strWrite) + 1);
    printf("client strRead = %s\n", strRead);
    close(sfd);
}
char * split(char*buff){
    char *token = strtok(buff, delim);
    do {
        sum = 0;
        printf("token = %s ", token);
        for (int l = 0; l < strlen(str); l++)
            sum += *(token + l);
        printf(" sum = %d\n", sum);
    } while ((token = strtok(NULL, delim)) != NULL);
}