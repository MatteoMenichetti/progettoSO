#include "../lib/ipc.h"

#define LOGPOS "../logs/system_log"
#define VOTEDPOS "../logs/voted_output"
#define LOGVALUE 0
#define VOTEDVALUE 4
#define WATCHVALUE 5
#define FALLIMENTO "FALLIMENTO \n"
#define SUCCESSO "SUCCESSO \n"

void writeOnLog(int *fd, char *buffer) {
    if ((write(fd[VOTEDVALUE], buffer, strlen(buffer))) == -1) {
        perror("DF: write on voted_output");
        exit(EXIT_FAILURE);
    }

    if ((write(fd[WATCHVALUE], IMALIVE, strlen(IMALIVE))) == -1) {
        perror("DF: write on voted_output");
        exit(EXIT_FAILURE);
    }
}

void initializationPIPE() {
    unlink(WATCHPPOS);
    if ((mknod(WATCHPPOS, S_IFIFO, DEFAULT)) == -1) {
        perror("watchdog: mknod");
        exit(EXIT_FAILURE);
    }
    chmod(WATCHPPOS, 0777);
}

void openFILE(int *fd) {
    if (((fd[LOGVALUE] = open(LOGPOS, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)) {
        perror("DF: open log");
        exit(EXIT_FAILURE);
    }

    if (!(fd[VOTEDVALUE] = open(VOTEDPOS, O_WRONLY | O_CREAT | O_TRUNC, 0666))) {
        perror("DF: open voted_output");
        exit(EXIT_FAILURE);
    }
}

void openPIPE(int *fd) {

    if (((fd[WATCHVALUE] = open(WATCHPPOS, O_WRONLY))) == -1) {
        perror("DF: open WATCHDOG pipe");
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
    int fd[6], failure_pid, valueSplitSum[3], i = 1;

    initializationPIPE();

    printf("DF: avvio FM\n");
    if (!(failure_pid = fork()))
        execl("./failure_manager", "failure_manager", (char *) NULL);

    printf("DF: avvio watchdog\n");
    if (!(fork())) {
        char *cFP = (char *) calloc(1, sizeof(failure_pid));
        sprintf(cFP, "%d", failure_pid);
        execl("./watchdog", "watchdog", cFP, (char *) NULL);
    }

    openPIPE(fd);
    openFILE(fd);

    while (0 == 0) {
        if ((read(fd[P1], (valueSplitSum + P1 - 1), sizeof(int))) == -1) perror("DF: read P1");

        if ((read(fd[P2], (valueSplitSum + P2 - 1), sizeof(int))) == -1) perror("DF: read P2");

        if ((read(fd[P3], (valueSplitSum + P3 - 1), sizeof(int))) == -1) perror("DF: read P3");

        dprintf(fd[LOGVALUE], "READ %d : p1 = %d p2 = %d p3 = %d \n", i, valueSplitSum[P1 - 1], valueSplitSum[P2 - 1], valueSplitSum[P3 - 1]);

        if (!EqualCondition(valueSplitSum[P1 - 1], valueSplitSum[P2 - 1], valueSplitSum[P3 - 1])) {
            writeOnLog(fd, FALLIMENTO);
            kill(failure_pid, SIGUSR1);
        } else {
            i++;
            writeOnLog(fd, SUCCESSO);
        }

    }
}

