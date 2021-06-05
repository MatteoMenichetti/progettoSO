#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    /*
      * avvio processi
      * input manager avvia P1,  P2, P3
      * decision_function avvia failure_manager
      */

    if (argc < 2) {
        printf("numero argomenti non suff.\n");
        exit(EXIT_FAILURE);
    }
    printf("%s %s\n", argv[1], argv[2]);

    printf("main: avvio decision_function\n");
    int pid, e;
    if (!(pid = fork())) {
        for (int i = 0; i < 3; i++) {
            printf("main: mi sospendo\n");
           if (pause() == -1) {
                printf("main: pause");
                exit(EXIT_FAILURE);
            }
        }
        e = execl("./decision_function", (char *) NULL);
        printf("main fork 1 IM: exec = %d\n", e);
    }

    printf("main: avvio input_manager\n");

    if (!fork()) {
        char *cpid = calloc(1, sizeof(char));
        sprintf(cpid, "%d", pid);
        printf("main: cpid = %s\n", cpid);
        e = execl("./input_manager", argv[1], argv[2], cpid, (char *) NULL);
        if (e == -1) {
            perror("main: seconda fork");
            exit(EXIT_FAILURE);
        }
        printf("main fork 2 IM: exec = %d", e);
    }
    return 0;
}
