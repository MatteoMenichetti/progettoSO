#include "../lib/ipc.h"

#define LOGPATH "../logs/system_log"
#define VOTEDPATH "../logs/voted_output"

#define WATCHDOG 0
#define FAILURE_MANAGER 1
#define VOTEDPOS 3
#define LOGPOS 4

#define FALLIMENTO "FALLIMENTO\n"
#define SUCCESSO "SUCCESSO\n"

void writeOnLog(int fd[], int valueSplitSum[], char buffer[]){
    dprintf(fd[LOGPOS], "p1 = %d p2 = %d p3 = %d \n", valueSplitSum[P1 - 1],
            valueSplitSum[P2 - 1],
            valueSplitSum[P3 - 1]);

    if ((write(fd[VOTEDPOS], buffer, strlen(buffer))) == -1) {
        perror("DF: write on voted_output");
        exit(EXIT_FAILURE);
    }
}

int EqualityCondition(int vp1, int vp2, int vp3) {
    if (vp1 != vp2 && vp1 != vp3 && vp2 != vp3)return 0;
    return 1;
}

void controllValueRecived(int *fd, int *pid, int *valueSplitSum) {
    char *buffer;
    printf("decision_function: valueSplitSum[P1 - 1] = %d, valueSplitSum[P2 - 1] = %d, valueSplitSum[P3 - 1] = %d\n",
           valueSplitSum[P1 - 1], valueSplitSum[P2 - 1], valueSplitSum[P3 - 1]);//eliminare
    if (!EqualityCondition(valueSplitSum[P1 - 1], valueSplitSum[P2 - 1], valueSplitSum[P3 - 1]))
        buffer = FALLIMENTO;
    else buffer = SUCCESSO;

    writeOnLog(fd, valueSplitSum, buffer);

    if ((strcmp(buffer, FALLIMENTO)) == 0) {
        printf("decision_function: send SIGUSR1 to failure_manager (FALLIMENTO)\n");
        kill(pid[FAILURE_MANAGER], SIGUSR1);
    }
    printf("decision_function: send signal (I_AM_ALIVE) to watchdog\n");
    if ((kill(pid[WATCHDOG], SIGUSR1)) == -1) {
        perror("decision_function: kill on watchdog");
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
    printf("decision_function: fd[LOGPOS] = %d, fd[VOTEDPOS] = %d\n", fd[LOGPOS], fd[VOTEDPOS]); //eliminare
}

void openPIPES(int fd[]) {
    char *paths[3] = {PIPEDP1PATH, PIPEDP2PATH, PIPEDP3PATH};
    printf("DF: *path[0] = %s , *path[1] = %s, *path[2] = %s\n", paths[0], paths[1], paths[2]);//eliminare
    int flags[3] = {O_RDONLY, O_RDONLY, O_RDONLY};
    for (int i = 0; i < 3; i++)
        fd[i] = openPIPE(paths[i], flags[i]);
    printf("DF: apertura PIPES fd[0] = %d, fd[1] = %d, fd[2] = %d, fd[3] = %d\n", fd[0], fd[1], fd[2],
           fd[3]);//eliminare
}

int main(void) {
    signal(SIGUSR1, SIG_IGN);

    int fd[5], pid[2], valueSplitSum[3];

    printf("DF: avvio FM\n");
    if (!(pid[FAILURE_MANAGER] = fork()))
        execl("./failure_manager", (char *) NULL);

    printf("DF: avvio watchdog\n");

    if (!(pid[WATCHDOG] = fork())) {
        char *failure_manager_pid = (char *) calloc(1, sizeof(pid[FAILURE_MANAGER]));
        sprintf(failure_manager_pid, "%d", pid[FAILURE_MANAGER]);
        execl("./watchdog", "watchdog", failure_manager_pid, (char *) NULL);
    }

    printf("decision_function: open FILE\n");
    openFILE(fd);
    printf("decision_function: open PIPES\n");
    openPIPES(fd);
    printf("DF: fd[P1] = %d, fd[P2] = %d, fd[P3] = %d, fd[LOGPOS] = %d, fd[VOTEDPOS] = %d\n", fd[P1], fd[P2], fd[P3],
           fd[LOGPOS], fd[VOTEDPOS]);//eliminare

    while (0 == 0) {
        printf("decision_function: read from p pipe\n");
        if ((read(fd[P1 - 1], &valueSplitSum[P1 - 1], sizeof(int))) == -1) perror("DF: read P1");

        if ((read(fd[P2 - 1], &valueSplitSum[P2 - 1], sizeof(int))) == -1) perror("DF: read P2");

        if ((read(fd[P3 - 1], &valueSplitSum[P3 - 1], sizeof(int))) == -1) perror("DF: read P3");
        printf("DF:  read fd[P1] = %d, fd[P2] = %d, fd[P3] = %d\n", valueSplitSum[P1 - 1], valueSplitSum[P2 - 1],
               valueSplitSum[P3 - 1]);//eliminare

        controllValueRecived(fd, pid, valueSplitSum);

    }
}

