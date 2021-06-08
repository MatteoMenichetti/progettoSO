#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void trap(int sig) { /* do nothing */ }

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("main: numero argomenti non suff.");
        exit(EXIT_FAILURE);
    }
    char *cpid = calloc(1, sizeof(char));
    sprintf(cpid, "%d", getpid());
    char c;
    signal(SIGCONT, trap);
    printf("main: avvio i tre P\n");
    for (int NP = 1; NP <= 3; NP++) {
        if (!fork()) {
            c = NP + 48;
            int e = execl("./p","p", argv[1], &c, cpid, (char *) 0);
            if (e == -1) {
                perror("m: execl");
                exit(EXIT_FAILURE);
            }
        }
        pause();
    }

    int pid_decision = fork();
    if (pid_decision == 0) {
        execl("./decision_function", "", NULL);
    } else {
        execl("./input_manager", argv[2], NULL);
    }
}
