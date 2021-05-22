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
    int csfd = definesocket();
    connecting(sfd);
    char buff[BUFSIZ];
    if (read(csfd, buff, sizeof(buff)) == -1) {
        perror("P2: lettura socket");
        exit(EXIT_FAILURE);
    }
    splitP2(buff, psfd);
    close(psdf);
}

void splitP2(char *buff, int psfd) {
    char *token, *lastWorld, c;
    int cmp = 0;
    for (int i = 0; i < strlen(buff); i++) {
        lastWorld = (buff + i);
        for (int j = i + 1; j < strlen(buff); j++) {
            c = *(buff + j);
            cmp = (c - delim);
            if ((c - delim) <= 0) {
                token = malloc((j + i) * sizeof(char));
                strncpy(token, (buff + i), j);
                printf("token = %s\n", token);
                int s = sum(token, 0);
                printf("%d\n", s);
                i += (j + 1);
                break;
            }
        }
    }
}

