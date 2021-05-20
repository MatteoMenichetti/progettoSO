#include <signal.h>
#include <unistd.h>

static int received_SIGUSR1 = 0;
int pids[3];

void funzione(int sig) {
    for (int i = 0; i < 3; i++) {
        kill(pids[i], SIGKILL);
    }
    kill(getpid(), SIGKILL);
}


int main(int argc, char *argv[]) {
    for (int i = 0; i < 3; i++) {
        pids[i] = *argv[i];
    }
    signal(SIGUSR1, funzione);
    while (received_SIGUSR1 == 0) {
        sleep(1);
    }
}