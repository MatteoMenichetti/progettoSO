#include "../lib/ipc.h"

int failure_pid = 0;

void USR1_handler() {
    printf("watchdog: inivio SIGUSR1 a FM (%d)\n", failure_pid);
    kill(failure_pid, SIGUSR1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("watchdog: numero argomenti insuff.");
        exit(EXIT_FAILURE);
    }

    failure_pid = atoi(argv[1]);

    int fd = *openPIPE((char **) &WATCHPATH, 1, O_RDONLY);

    char *buff = (char *) calloc(1, strlen(IMALIVE));

    signal(SIGALRM, USR1_handler);

    while (0 == 0) {
        alarm(3);
        if ((read(fd, buff, sizeof(buff))) == -1) {
            perror("watchdog: lettura");
            exit(EXIT_FAILURE);
        }
        if ((strcmp(buff, IMALIVE)) == 0) {
            alarm(0);
        }
    }
}
