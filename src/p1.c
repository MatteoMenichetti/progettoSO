#include "../lib/p.h"

void p1(int flag) {
    int pfd = open(PIPEADDR, O_RDONLY);
    int pfddf = open(PIPEDP1, O_RDONLY);
    char buff[BUFSIZ];
    while (0 == 0) {
        int r = read(pfd, buff, sizeof(buff));
        printf("pfd = %d", r);
        printf("P1: legge = %s\n", buff);
        splitP1(buff, pfddf, flag);
    }
}

void splitP1(char *buff, int pfddf, int flag) {
    char *token = strtok(buff, delim);
    int s;
    do {
        printf("P1: token = %s\n", token);
        s = sum(token, 0);
        if (flag == ACTIVE_FAILURE)errsum(&s, 10);
        printf("P1: invio a DF %d\n", s);
        if (write(pfddf, &s, sizeof(s)) == -1) {
            perror("P1: write");
            exit(EXIT_FAILURE);
        }
    } while ((token = strtok(NULL, delim)) != NULL);
}