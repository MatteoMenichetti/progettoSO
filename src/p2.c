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
    strcpy(sockServer.sun_path, SOCKPATH);
    sockServer.sun_family = AF_UNIX;
    while ((connect(sfd, (struct sockaddr *) &sockServer, sizeof(sockServer))) == -1) {
        perror("P2: connect");
        sleep(1);
    }
}

void p2(int modality, int pid) {
    createPIPE(PIPEDP2PATH);
    kill(pid, SIGCONT);

    int psfd, flag = O_WRONLY,csfd = definesocket(), s = 0;
    char *path = PIPEDP2PATH, buff[BUFSIZ], *token = (char *) calloc(1, sizeof(char));

    psfd = openPIPE(path, flag);

    connecting(csfd);

    while (0 == 0) {
        if((read(csfd, buff, sizeof(buff)))==-1){
            perror("P1: read from pipe");
            exit(EXIT_FAILURE);
        }

        token = splitP2(buff);
        s = sum(token, strlen(token));

        if (modality == ACTIVE_FAILURE) errsum(&s, 20);

        printf("P2: send to DF %d\n", s);

        if (write(psfd, &s, sizeof(s)) == -1) {
            perror("P1: write");
            exit(EXIT_FAILURE);
        }

        strncpy(buff, "\0", strlen(buff));
    }
}


char *splitP2(char *buff) {
    int s = 0;
    char *token = calloc(1, sizeof(char));
    for (int i = 0; i < (strlen(buff)); i++) {
        if (strncmp((buff + i), delim, 1) != 0) {
            token = (char *) realloc(token, strlen(token) + 1);
            token[s] = buff[i];
            s++;
        }
    }
    return token;
}