#include "../lib/common.h"

void SIGCONT_handler() { /* do nothing */ }

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("main: less than 2 arguments");
        exit(EXIT_FAILURE);
    }

    char *cpid = calloc(1, sizeof(char)), c;

    sprintf(cpid, "%d", getpid());

    signal(SIGCONT, SIGCONT_handler);
    printf("main: avvio i tre P\n");
    for (int NP = 1; NP <= 3; NP++) {
        if (!fork()) {
            c = NP + 48;
            printf("%c ", c);
            int e = execl("./p", "p", argv[1], &c, cpid, (char *) 0);
            if (e == -1) {
                perror("m: execl");
                exit(EXIT_FAILURE);
            }
        }
        pause();
    }

    int pid_decision = fork();
    if (pid_decision == 0) {
        printf("main: avvio DF\n");
        execl("./decision_function", "decision_function", NULL);
    } else {
        printf("main: avvio IM\n");
        execl("./input_manager", "input_manger", argv[2], NULL);
    }
}
