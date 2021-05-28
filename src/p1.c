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

    int pfddf;

    /*if ((pfddf = open(PIPEDP3, O_WRONLY))) {
        perror("P3: open pipe");
        exit(EXIT_FAILURE);
    }*/

    printf("P1: open PIPEDP1 eseguita\n");
    char buff[BUFSIZ];
    while (0 == 0) {
        int r = read(pfd, buff, sizeof(buff));
        printf("pfd = %d\n", r);
        printf("P1: legge = %s\n", buff);
        splitP1(buff/*, pfddf*/, flag);
    }
}

void splitP1(char *buff/*, int pfddf*/, int flag) {
    char *token = strtok(buff, delim);
    int s;
    do {
        printf("P1: token = %s\n", token);
        s = sum(token, 0);
        if (flag == ACTIVE_FAILURE)errsum(&s, 10);
        printf("P1: invio a DF %d\n", s);
        /*if (write(pfddf, &s, sizeof(s)) == -1) {
            perror("P1: write");
            exit(EXIT_FAILURE);
        }*/
    } while ((token = strtok(NULL, delim)) != NULL);
}