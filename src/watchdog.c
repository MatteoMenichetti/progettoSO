#include "../lib/common.h"

int allarme = 0;

void SIGALRM_handler() {
    allarme = 1;
}

void SIGUSR1_handler() {
    printf("watchdog: SIGUSR1_handler \n");
    alarm(2);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("watchdog: less than 2 arguments");
        exit(EXIT_FAILURE);
    }

    printf("watchdog start\n");

    int pid_failure_manager = atoi(argv[1]);

    signal(SIGUSR1, SIGUSR1_handler);
    signal(SIGALRM, SIGALRM_handler);

    alarm(2);

    while (allarme == 0) { pause(); };

    kill(pid_failure_manager, SIGUSR1);
}

