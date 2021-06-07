#include "../lib/ipc.h"

#define LOGPOS "../logs/system_log"
#define VOTEDO "../logs/voted_output"
#define LOGVALUE 0
#define FALLIMENTO "FALLIMENTO \n"
#define SUCCESSO "SUCCESSO \n"

void writeOnLog(int fd, char *buffer) {
    write(fd, buffer, strlen(buffer));
}

void openPIPE(int *fd) {

    if (((fd[LOGVALUE] = open(LOGPOS, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)) {
        perror("DF: open log");
        exit(EXIT_FAILURE);
    }
    if ((fd[P1] = open(PIPEDP1, O_RDONLY)) == -1) {
        perror("DF: open pipedp1");
        exit(EXIT_FAILURE);
    }

    if ((fd[P2] = open(PIPEDP2, O_RDONLY)) == -1) {
        perror("DF: open pipedp2");
        exit(EXIT_FAILURE);
    }

    if ((fd[P3] = open(PIPEDP3, O_RDONLY)) == -1) {
        perror("DF: open pipedp3");
        exit(EXIT_FAILURE);
    }

}

int EqualCondition(int vp1, int vp2, int vp3) {
    if (!(vp1 == vp2) && !(vp1 == vp3) && !(vp2 == vp3))return 0;
    return 1;
}

int main(void) {
    int fd[4], pid, vp[3], i = 1, voted_output = open(VOTEDO, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (!(pid = fork()))
        execl("./failure_manager", "failure_manager", NULL);
    openPIPE(fd);
    while (0 == 0) {
        if ((read(fd[P1], (vp + P1 - 1), sizeof(int))) == -1) perror("DF: read P1");

        if ((read(fd[P2], (vp + P2 - 1), sizeof(int))) == -1) perror("DF: read P2");

        if ((read(fd[P3], (vp + P3 - 1), sizeof(int))) == -1) perror("DF: read P3");

        dprintf(voted_output, "READ %d : p1 = %d p2 = %d p3 = %d \n", i, vp + P1 - 1, vp + P2 - 1, vp + P3 - 1);

        if (!EqualCondition(vp[P1 - 1], vp[P2 - 1], vp[P3 - 1])) {
            writeOnLog(fd[LOGVALUE], FALLIMENTO);
            kill(pid, SIGUSR1);
        } else {
            i++;
            writeOnLog(fd[LOGVALUE], SUCCESSO);
        }

    }
}

