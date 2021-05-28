#include "../lib/p.h"

void p1(int pdfd) {
    int pfd = open(PIPEADDR, O_RDONLY);
    char buff[BUFSIZ];
    while (0 == 0) {
        int r = read(pfd, buff, sizeof(buff));
        printf("pfd = %d", r);
        printf("P1: legge = %s\n", buff);
        splitP1(buff, pdfd);
    }
}

void splitP1(char *buff, int pfd) {
    char *token = strtok(buff, delim);
    int s;
    do {
        printf("P1: token = %s\n", token);
        s = sum(token);
#ifdef ERR
        if(!ERR)
        s +=10;
#endif
        printf("P1: invio a DF %d\n", s);
        if (write(pfd, &s, sizeof(s)) == -1) {
            perror("P1: write");
            exit(EXIT_FAILURE);
        }
    } while ((token = strtok(NULL, delim)) != NULL);
}