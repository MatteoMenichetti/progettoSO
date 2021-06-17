#include "../lib/common.h"
// handler che uccide tutti i processi
void SIGUSR1_handler() {
    printf("failure_manager: kill all\n");
    kill(0, SIGKILL);
}

int main(void) {
    printf("failure_manager: start\n");
    // ridefinisce l'handler del segnale SIGUSR1
    signal(SIGUSR1, SIGUSR1_handler);
    int status;
    // metto in attesa failure manager
    do { status = pause(); } while (status != -1);

}