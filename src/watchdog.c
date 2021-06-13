#include "../lib/ipc.h"

int allarme = 0;

void handler() {
    allarme = 1;
}

void I_AM_ALIVE() {
    printf("I AM ALIVE \n");
    alarm(2);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("watchdog: numero argomenti insuff.");
        exit(EXIT_FAILURE);
    }
    int pid_failure_manager = atoi(argv[0]);
    printf("ho aperto watchDog \n");
    signal(SIGUSR1, I_AM_ALIVE);
    signal(SIGALRM, handler);
    alarm(2);
    while (allarme == 0) { pause(); };
    kill(pid_failure_manager, SIGUSR1);
}

