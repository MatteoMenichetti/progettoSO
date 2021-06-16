#include "../lib/common.h"

void SIGUSR1_handler() {
    printf("failure_manager: kill all\n");
    kill(0, SIGKILL);
}

int main(void) {
    printf("failure_manager: start\n");
    signal(SIGUSR1, SIGUSR1_handler);
    int status;
    do { status = pause(); } while (status != -1);

}