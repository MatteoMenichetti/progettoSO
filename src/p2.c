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
    if ((psfd = open(PIPEDP2, O_WRONLY)) == -1) {
        perror("P2: open pipe");
        exit(EXIT_FAILURE);
    }
    int csfd = definesocket();
    connecting(csfd);
    char buff[BUFSIZ];
    while (0 == 0) {
        if (read(csfd, buff, sizeof(buff)) == -1) {
            perror("P2: lettura socket");
            exit(EXIT_FAILURE);
        }
        splitP2(buff, psfd, flag, strlen(buff), 20);
    }
    close(psfd);
}

void splitP2(char *buff, int psfd, int flag, int start, int value) {
    char *token;
    int s;
    for (int i = 0; i < strlen(buff); i++) {
        for (int j = i + 1; j < strlen(buff); j++) {
            if ((*(buff + j) - *delim) <= 0) {
                token = malloc((j + i) * sizeof(char));
                strncpy(token, (buff + i), j);
                printf("token = %s", token);
                s = sum(token, start);
                if (flag == ACTIVE_FAILURE)errsum(&s, value);
                write(psfd, &s, sizeof(s));
                printf(" s = %d\n", s);
                i += (j + 1);
                break;
            }
        }
    }
}


