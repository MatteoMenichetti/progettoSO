#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    printf("Hello, World!\n");

    /*
     * avvio processi
     * input manager avvia P1,  P2, P3
     * decision_function avvia failure_manager
     */

    if (!fork())
        execl("./input_manager", "./input_manager", *argv[1], *argv[2], NULL);
    if (!fork())
        execl("./decision_function", "./decision_function", NULL);
    return 0;
}
