#include "../lib/ipc.h"
#include <stdlib.h>
#include <signal.h>

#define LOGPOS "../logs/system_log"
#define LOGVALUE 0
#define FALLIMENTO "FALLIMENTO"
#define SUCCESSO "SUCCESSO"

void writeOnLog(int fd, char *buffer) { write(fd, buffer, sizeof(buffer)); }

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
    int fd[4], pid;
    char *vp1, *vp2, *vp3;
    if (!(pid = fork()))
        execl("./failure_manager", "./failure_manager", NULL);
    opens(fd);
    while (0 == 0) {
        printf("DF: leggo\n");
        if (read(fd[P1], vp1, sizeof(int)) == -1)perror("DF: read P1");
        if (read(fd[P2], vp2, sizeof(int)) == -1)perror("DF: read P2");
        if (read(fd[P3], vp3, sizeof(int)) == -1)perror("DF: read P3");
        if (!strcmp(vp1, vp2) || !strcmp(vp1, vp3) || !strcmp(vp2, vp3)) {

            writeOnLog(fd[LOGVALUE], FALLIMENTO);
            kill(pid, SIGUSR1);
        } else writeOnLog(fd[LOGVALUE], SUCCESSO);
    }
}