#include "../lib/ipc.h"
#include <stdlib.h>

#define LOGPOS "../logs/system_log"
#define LOGVALUE 0

void opens(int *fd) {
    printf("DF: apertura LOGFILE\n");
    if ((fd[LOGVALUE] = open(LOGPOS, O_WRONLY | O_CREAT, 0666) == -1)) {
        perror("DF: open log");
        exit(EXIT_FAILURE);
    }
    printf("DF: apertura PIPEDP1\n");
    if ((fd[P1] = open(PIPEDP1, O_RDONLY) == -1)) {
        perror("DF: open pipedp1");
        exit(EXIT_FAILURE);
    }

    printf("DF: apertura PIPEDP2\n");
    if ((fd[P2] = open(PIPEDP2, O_RDONLY) == -1)) {
        perror("DF: open pipedp2");
        exit(EXIT_FAILURE);
    }

    printf("DF: apertura PIPEDP3\n");
    if ((fd[P3] = open(PIPEDP3, O_RDONLY) == -1)) {
        perror("DF: open pipedp3");
        exit(EXIT_FAILURE);
    }

    printf("DF: fine opens\n");
}

int main(void) {
    int fd[4], nr;
    char *vp1, *vp2, *vp3;
    opens(fd);
    while (0 == 0) {
        printf("DF: leggo\n");
        if (read(fd[P1], vp1, sizeof(int)) == -1)perror("DF: read P1");
        if (read(fd[P2], vp2, sizeof(int)) == -1)perror("DF: read P2");
        if (read(fd[P3], vp3, sizeof(int)) == -1)perror("DF: read P3");
    }
}