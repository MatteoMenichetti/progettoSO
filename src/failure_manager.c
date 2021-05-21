#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 5

static int received_SIGUSR1 = 0;
int pids[N];

void funzione(int sig) {
    for (int i = 0; i < N; i++) {
        kill(pids[i], SIGKILL);
    }
    printf("failure_manager: mi uccido\n");
    kill(getpid(), SIGKILL);
}


int main(int argc, char *argv[]) {
    printf("%d\n", getpid());
    for (int i = 0; i < N; i++) {
        pids[i] = *argv[i];
    }
    signal(SIGUSR1, funzione);
    int status;
    do { status = pause();} while (status != -1);

}