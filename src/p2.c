#include "../lib/p.h"

struct Token {
    char *token;
    struct Token *previous;
} tokenLL;


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
        struct Token *p=&tokenLL, *tmp=p;
        do {
            sum(p->token, &s);
            if (p->previous == NULL) {
                int i = 0;
                i++;
            }
            p = p->previous;
        } while (p != NULL);
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


void operation(struct Token *token, char *buff, int *s, int i, int n) {
    token->previous = calloc(1, sizeof(struct Token));
    if (tokenLL.token == NULL) {
        tokenLL.token = calloc(strlen(buff + i), sizeof(char));
        strncpy(tokenLL.token, buff + i, n);
    } else {
        token->token = calloc(strlen(buff + i), sizeof(char));
        strncpy(token->token, buff + i, n);
        if (i == 0) {
            free(token->previous);
            token->previous = NULL;
        }
    }
}

void splitP2(char *buff, int *s, int flag, int start, int value) {
    struct Token *token = &tokenLL;
    int lastDelimiter = strlen(buff);
    for (int i = strlen(buff) - 1; i > 0; i--) {
        if (strncmp((buff + i), delim, 1) == 0) { //strncmp((buff+i), delim, 1) (*(buff + i) - *delim)
            operation(token, buff, s, i + 1, lastDelimiter - i - 1);
            token = token->previous;
            lastDelimiter = i;
        }
    }
    operation(token, buff, s, 0, lastDelimiter);
    printf("P2: s = %d\n", *s);
}