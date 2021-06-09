#include "../lib/ipc.h"

#define LOGPATH "../logs/system_log"
#define VOTEDPATH "../logs/voted_output"

#define WATCHPOS 4
#define VOTEDPOS 5
#define LOGPOS 6

#define FALLIMENTO "FALLIMENTO \n"
#define SUCCESSO "SUCCESSO \n"

void writeOnLog(int *fd, char *buffer) {
    if ((write(fd[VOTEDPOS], buffer, strlen(buffer))) == -1) {
        perror("DF: write on voted_output");
        exit(EXIT_FAILURE);
    }

    if ((write(fd[WATCHPOS], IMALIVE, strlen(IMALIVE))) == -1) {
        perror("DF: write on voted_output");
        exit(EXIT_FAILURE);
    }
}

void openFILE(int *fd) {
    if (((fd[LOGPOS] = open(LOGPATH, O_WRONLY | O_CREAT | O_TRUNC, PERMISIONFILE)) == -1)) {
        perror("DF: open log");
        exit(EXIT_FAILURE);
    }

    if ((fd[VOTEDPOS] = open(VOTEDPATH, O_WRONLY | O_CREAT | O_TRUNC, PERMISIONFILE)) == -1) {
        perror("DF: open voted_output");
        exit(EXIT_FAILURE);
    }
}


int EqualCondition(int vp1, int vp2, int vp3) {
    if (!(vp1 == vp2) && !(vp1 == vp3) && !(vp2 == vp3))return 1;
    return 0;
}

void createPIPES() {
    char *pipes[4] = {WATCHPATH, PIPEDP1PATH, PIPEDP2PATH, PIPEDP3PATH};
    createPIPE(pipes, 4);
}

void openPIPES(int fd[]) {
    char *paths[4] = {PIPEDP1PATH,PIPEDP2PATH, PIPEDP3PATH, WATCHPATH};
    int flags[4] = {O_WRONLY, O_RDONLY, O_RDONLY, O_RDONLY};
    fd = openPIPE(paths, 4, flags);
}

int main(void) {
    int fd[7], failure_pid, valueSplitSum[3], i = 1;

    createPIPES();

    printf("DF: avvio FM\n");
    if (!(failure_pid = fork()))
        execl("./failure_manager", "failure_manager", (char *) NULL);

    printf("DF: avvio watchdog\n");

    if (!(fork())) {
        char *cFP = (char *) calloc(1, sizeof(failure_pid));
        sprintf(cFP, "%d", failure_pid);
        execl("./watchdog", "watchdog", cFP, (char *) NULL);
    }

    openPIPES(fd);
    openFILE(fd);

    while (0 == 0) {
        if ((read(fd[P1 - 1], (valueSplitSum + P1 - 1), sizeof(int))) == -1) perror("DF: read P1");

        if ((read(fd[P2 - 1], (valueSplitSum + P2 - 1), sizeof(int))) == -1) perror("DF: read P2");

        if ((read(fd[P3 - 1], (valueSplitSum + P3 - 1), sizeof(int))) == -1) perror("DF: read P3");

        dprintf(fd[LOGPOS], "READ %d : p1 = %d p2 = %d p3 = %d \n", i, valueSplitSum[P1 - 1],
                valueSplitSum[P2 - 1],
                valueSplitSum[P3 - 1]);

        if (!EqualCondition(valueSplitSum[P1 - 1], valueSplitSum[P2 - 1], valueSplitSum[P3 - 1])) {
            writeOnLog(fd, FALLIMENTO);
            kill(failure_pid, SIGUSR1);
        } else {
            i++;
            writeOnLog(fd, SUCCESSO);
        }

    }
}

