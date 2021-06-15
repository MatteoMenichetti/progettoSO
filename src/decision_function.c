#include "../lib/ipc.h"

#define LOGPATH "../logs/system_log"
#define VOTEDPATH "../logs/voted_output"

#define VOTEDPOS 3
#define LOGPOS 4

#define FALLIMENTO "FALLIMENTO \n"
#define SUCCESSO "SUCCESSO \n"

void writeOnLog(int fd, int pid_failure_manager, char *buffer) {
    if ((write(fd, buffer, strlen(buffer))) == -1) {
        perror("DF: write on voted_output");
        exit(EXIT_FAILURE);
    }
    if ((kill(pid_failure_manager, SIGUSR1)) == -1) {
        perror("decision_function: kill on failure_manager");
        exit(EXIT_FAILURE);
    }
}

void openFILE(int *fd) {
    if (((fd[LOGPOS] = open(LOGPATH, O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONFILE)) == -1)) {
        perror("DF: open log");
        exit(EXIT_FAILURE);
    }

    if ((fd[VOTEDPOS] = open(VOTEDPATH, O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONFILE)) == -1) {
        perror("DF: open voted_output");
        exit(EXIT_FAILURE);
    }
}

int EqualityCondition(int vp1, int vp2, int vp3) {
    if (vp1 != vp2 && vp1 != vp3 && vp2 != vp3)return 1;
    return 0;
}

void openPIPES(int fd[]) {
    char *paths[3] = {PIPEDP1PATH, PIPEDP2PATH, PIPEDP3PATH};
    printf("DF: *path[0] = %s , *path[1] = %s, *path[2] = %s\n", paths[0], paths[1], paths[2]);
    int flags[3] = {O_RDONLY, O_RDONLY, O_RDONLY};
    for (int i = 0; i < 3; i++)
        fd[i] = openPIPE(paths[i], flags[i]);
    printf("DF: apertura PIPES fd[0] = %d, fd[1] = %d, fd[2] = %d, fd[3] = %d\n", fd[0], fd[1], fd[2], fd[3]);
}

int main(void) {
    signal(SIGUSR1, SIG_IGN);
    int fd[5], failure_pid, watchdog_pid, valueSplitSum[3], i = 1;

    printf("DF: avvio FM\n");
    if (!(failure_pid = fork()))
        execl("./failure_manager", "failure_manager", (char *) NULL);

    printf("DF: avvio watchdog\n");

    if (!(watchdog_pid = fork())) {
        char *cFP = (char *) calloc(1, sizeof(failure_pid));
        sprintf(cFP, "%d", failure_pid);
        execl("./watchdog", "watchdog", cFP, (char *) NULL);
    }

    printf("DF: open FILE\n");
    openFILE(fd);
    printf("DF: open PIPES\n");
    openPIPES(fd);
    printf("DF: fd[P1] = %d, fd[P2] = %d, fd[P3] = %d, fd[LOGPOS] = %d, fd[VOTEDPOS] = %d\n", fd[P1], fd[P2], fd[P3],
           fd[LOGPOS], fd[VOTEDPOS]);

    while (0 == 0) {
        printf("DF: read\n");
        if ((read(fd[P1 - 1], (valueSplitSum + P1 - 1), sizeof(int))) == -1) perror("DF: read P1");

        if ((read(fd[P2 - 1], (valueSplitSum + P2 - 1), sizeof(int))) == -1) perror("DF: read P2");

        if ((read(fd[P3 - 1], (valueSplitSum + P3 - 1), sizeof(int))) == -1) perror("DF: read P3");
        printf("DF:  read fd[P1] = %s, fd[P2] = %s, fd[P3] = %s\n", valueSplitSum + P1 - 1, valueSplitSum + P2 - 1,
               valueSplitSum + P3 - 1);
        dprintf(fd[LOGPOS], "READ %d : p1 = %d p2 = %d p3 = %d \n", i, valueSplitSum[P1 - 1],
                valueSplitSum[P2 - 1],
                valueSplitSum[P3 - 1]);

        if (!EqualityCondition(valueSplitSum[P1 - 1], valueSplitSum[P2 - 1], valueSplitSum[P3 - 1])) {
            writeOnLog(fd[VOTEDPOS], watchdog_pid, FALLIMENTO);
            printf("DF: FALLIMENTO\n");
            kill(failure_pid, SIGUSR1);
        } else {
            i++;
            writeOnLog(fd[VOTEDPOS], watchdog_pid, SUCCESSO);
            printf("DF: SUCCESSO\n");
        }

    }
}

