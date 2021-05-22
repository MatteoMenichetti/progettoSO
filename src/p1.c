#include "../lib/p.h"

void p1(int modality, int sfd) {
    int pfd = open(PIPEADDR, O_RDONLY);
    char buff[100];
    while (0 == 0) {
        read(pfd, buff, 100);
        printf("P1: legge = %s\n", buff);
        split(buff);
    }
}

char *split(char *buff) {
    char *token = strtok(buff, delim);
    do {
        printf("token = %s ", token);
        int s=sum(token, 0);
    } while ((token = strtok(NULL, delim)) != NULL);
    return NULL;
}