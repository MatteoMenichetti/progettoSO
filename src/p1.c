#include "../lib/p.h"

void p1(int flag) {
    int pfd = open(PIPEADDR, O_RDONLY);

    printf("P1: eseguo unlink\n");
    unlink(PIPEDP1);
    if (mknod(PIPEDP1, S_IFIFO, DEFAULT) == -1) {
        perror("P: mknod");
        exit(EXIT_FAILURE);
    }
    printf("P1: mknod eseguito\n");
    chmod(PIPEDP1, 0777);

    int pfddf = 0;

    /*if ((pfddf = open(PIPEDP3, O_WRONLY))) {
        perror("P3: open pipe");
        exit(EXIT_FAILURE);
    }*/

    printf("P1: open PIPEDP1 eseguita\n");
    printf("pfd = %d\n", pfd);
    char buff[BUFSIZ];
    int s = 0, r = 0;
    while (0 == 0) {
        r = read(pfd, buff, sizeof(buff));
        printf("P1: legge = %s\n", buff);
        s = splitP1(buff/*, pfddf*/, flag);
        printf("s = %d\n", s);
    }
}

int splitP1(char *buff/*, int pfddf*/, int flag) {
    printf("P1: esecuzione strtok\n");
    char *token;
    token = strtok(buff, delim);
    printf("P1: token =  %s", buff);
    int s = 0;
    do {
        printf("P1: token = %s\n", token);
        s += sum(token, 0);
        if (flag == ACTIVE_FAILURE)errsum(&s, 10);

    } while ((token = strtok(NULL, delim)) != NULL);
    printf("P1: invio a DF %d\n", s);
    return s;
    /*if (write(pfddf, &s, sizeof(s)) == -1) {
        perror("P1: write");
        exit(EXIT_FAILURE);
    }*/
}