#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void funzione(int sig) {
    printf("FM: uccido tutti\n");
    kill(0, SIGKILL);
}


int main(void ) {
    printf("FM: %d\n", getpid());
    signal(SIGUSR1, funzione);
    int status;
    do { status = pause(); } while (status != -1);

}