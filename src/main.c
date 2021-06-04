#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    /*
      * avvio processi
      * input manager avvia P1,  P2, P3
      * decision_function avvia failure_manager
      */
    printf("%s %s\n", argv[1], argv[2]);
    printf("main: avvio input_manager\n");
    if (!fork())
        execl("./input_manager", "./input_manager", *argv[1], *argv[2], NULL);

    printf("main: avvio decision_function\n");
    if (!fork())
        execl("./decision_function", "./decision_function", NULL);
    return 0;
}
