#include "../lib/p.h"

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

void p2(int flag) {
    printf("P2: eseguo unlink\n");
    unlink(PIPEDP2);
    if (mknod(PIPEDP2, S_IFIFO, DEFAULT) == -1) {
        perror("P2: mknod");
        exit(EXIT_FAILURE);
    }
    chmod(PIPEDP2, 0777);
    int psfd;
    /* if ((psfd = open(PIPEDP2, O_WRONLY)) == -1) {
         perror("P2: open pipe");
         exit(EXIT_FAILURE);
     }*/
    int csfd = definesocket(), s = 0;
    connecting(csfd);
    char buff[BUFSIZ];
    while (0 == 0) {
        if (read(csfd, buff, sizeof(buff)) == -1) {
            perror("P2: lettura socket");
            exit(EXIT_FAILURE);
        }
        splitP2(buff, &s, flag, strlen(buff), 20);
        printf("P2: invio a DF %d\n", s);
        /*if (write(pfddf, &s, sizeof(s)) == -1) {
        perror("P1: write");
        exit(EXIT_FAILURE);
    }*/
        strncpy(buff, "\0", strlen(buff));
        s = 0;
    }
    close(psfd);
}

void tokenSum(char *token, char *buff, int *s, int i, int n) {
    token = calloc(strlen(buff + i), sizeof(char));
    strncpy(token, buff + i, n);
    sum(token, s);
    free(token);
}

void splitP2(char *buff, int *s, int flag, int start, int value) {
    char *token, last;
    for (int i = strlen(buff) - 1; i > 0; i--) {
        if ((*(buff + i) - *delim) == 0) {
            last = i;
            tokenSum(token, buff, s, i + 1, strlen(buff + i + 1));
        }
    }
    tokenSum(token, buff, s, 0, last);
    printf("s = %d\n", *s);

    if (flag == ACTIVE_FAILURE)errsum(s, value);
}


