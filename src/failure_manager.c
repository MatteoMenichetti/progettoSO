#include "../lib/common.h"

void USR1_handler() {
    printf("failure_manager: kill all\n");
    kill(0, SIGKILL);
}

int main(void) {
    printf("failure_manager: start\n");
    printf("FM: failure_pid = %d\n", getpid());//ELIMINARE
    signal(SIGUSR1, USR1_handler);
    int status;
    do { status = pause(); } while (status != -1);

}