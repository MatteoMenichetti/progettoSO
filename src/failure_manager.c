#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void funzione(int sig) {
    printf("failure_manager: uccido tutti\n");
    kill(0, SIGKILL);
}


int main(int argc, char *argv[]) {
    printf("%d\n", getpid());
    signal(SIGUSR1, funzione);
    int status;
    do { status = pause(); } while (status != -1);

}