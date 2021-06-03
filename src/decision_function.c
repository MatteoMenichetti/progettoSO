#include "../lib/ipc.h"
#include <signal.h>

#define LOGPOS "../logs/system_log"
#define VOTED "../logs/voted_output"
#define LOGVALUE 0
#define FALLIMENTO "FALLIMENTO\n"
#define SUCCESSO "SUCCESSO\n"

void writeOnLog(int fd, char *buffer) { write(fd, buffer, strlen(buffer)); }

void opens(int *fd) {
    printf("DF: apertura LOGFILE\n");
    if (((fd[LOGVALUE] = open(LOGPOS, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)) {
        perror("DF: open log");
        exit(EXIT_FAILURE);
    }
    printf("DF: apertura PIPEDP1\n");
    if ((fd[P1] = open(PIPEDP1, O_RDONLY)) == -1) {
        perror("DF: open pipedp1");
        exit(EXIT_FAILURE);
    }

    printf("DF: apertura PIPEDP2\n");
    if ((fd[P2] = open(PIPEDP2, O_RDONLY)) == -1) {
        perror("DF: open pipedp2");
        exit(EXIT_FAILURE);
    }

    printf("DF: apertura PIPEDP3\n");
    if ((fd[P3] = open(PIPEDP3, O_RDONLY)) == -1) {
        perror("DF: open pipedp3");
        exit(EXIT_FAILURE);
    }

    printf("DF: fine opens\n");
}


int main(void) {
    int fd[4], vp[3], pid;

    if (!(pid = fork()))
        execl("./failure_manager", "./failure_manager", NULL);
    opens(fd);
    int i = 1;
    int voted_output = open(VOTED, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    while (0 == 0) {
        dprintf(voted_output, "inizio iterazione riga %d \n", i);
        if ((read(fd[P1], vp + P1 - 1, sizeof(int))) == -1) { perror("DF: read P1"); }
        dprintf(voted_output, " p1: %d \n", vp[P1 - 1]);
        if ((read(fd[P2], vp + P2 - 1, sizeof(int))) == -1) { perror("DF: read P2"); }
        dprintf(voted_output, " p2: %d \n", vp[P2 - 1]);
        if ((read(fd[P3], vp + P3 - 1, sizeof(int))) == -1) { perror("DF: read P3"); }
        dprintf(voted_output, " p3: %d \n", vp[P3 - 1]);
        dprintf(voted_output, "fine iterazione riga %d \n", i);

        if (!(vp + P1 == vp + P2) && !(vp + P1 == vp + P3) && !(vp + P2 == vp + P3)) {
            writeOnLog(fd[LOGVALUE], FALLIMENTO);
            kill(pid, SIGUSR1);
        } else {
            i++;
            writeOnLog(fd[LOGVALUE], SUCCESSO);
        }
    }
}