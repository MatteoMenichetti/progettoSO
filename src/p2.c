#include "../lib/p.h"
#include "../lib/ipc.h"

int definesocket() {
    int csfd;
    printf("P2: esegue socket\n");
    if ((csfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT)) == -1) {
        perror("P2: socket");
        exit(0);
    }
    return csfd;
}

void connecting(int sfd) {
    struct sockaddr_un sockServer;
    strcpy(sockServer.sun_path, SOCKADDR);
    sockServer.sun_family = AF_UNIX;
    printf("P2: connessione socket");
    while ((connect(sfd, (struct sockaddr *) &sockServer, sizeof(sockServer))) == -1) {
        perror("client: connect");
        sleep(1);
    }
}

void p2(int psfd) {
#define LAST (str)strlen(str)
    int csfd = definesocket();
    connecting(psfd);
    char buff[BUFSIZ];
    if (read(csfd, buff, sizeof(buff)) == -1) {
        perror("P2: lettura socket");
        exit(EXIT_FAILURE);
    }
    splitP2(buff, psfd);
    close(psfd);
}

void splitP2(char *buff, int psfd) {
    char *token;
    int s;
    for (int i = 0; i < strlen(buff); i++) {
        for (int j = i + 1; j < strlen(buff); j++) {
            if ((*(buff + j) - *delim) <= 0) {
                token = malloc((j + i) * sizeof(char));
                strncpy(token, (buff + i), j);
                printf("token = %s", token);
                s = sum(token);
#ifdef ERR
                if(!ERR)
                s +=20;
#endif
                write(psfd, &s, sizeof(s));
                printf(" s = %d\n", s);
                i += (j + 1);
                break;
            }
        }
    }
}


