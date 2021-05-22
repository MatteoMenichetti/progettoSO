#include "../lib/p.h"

int definesocket() {
    int csfd;
    printf("P2: esegue socket\n");
    if ((csfd = socket(AF_UNIX, SOCK_STREAM, DEF)) == -1) {
        perror("P2: socket");
        exit(0);
    }
    return csfd;
}

void connecting(int sfd) {
    struct sockaddr_un sockServer;
    strcpy(sockServer.sun_path, SOCKADDR);
    sockServer.sun_family = AF_UNIX;
    printf("P2: connessione socket")
    while ((connect(csfd, (struct sockaddr *) &sockServer, sizeof(sockServer))) == -1) {
        perror("client: connect");
        sleep(1);
    }
}

void p2(int modality, int psdf) {
    int sfd = definesocket();
    connecting(sfd);
}

void splitP2(char *buff) {
    char *token = strtok(buff, delim);
    do {
        printf("token = %s ", token);
        int s = sum(token, 0);
    } while ((token = strtok(NULL, delim)) != NULL);
}
