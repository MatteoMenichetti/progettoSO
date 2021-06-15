#include "../lib/common.h"

void USR1_handler(int sig) {
    printf("failure_manager: uccido tutti\n");
    kill(0, SIGKILL);
}


int main(int argc, char *argv[]) {
    printf("FM: failure_pid = %d\n", getpid());
    signal(SIGUSR1, USR1_handler);
    int status;
    do { status = pause(); } while (status != -1);

}