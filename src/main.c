#include "../lib/common.h"

void SIGCONT_handler() { /* do nothing */ }

int main(int argc, char *argv[]) {
    //si controlla che siano passati il giusto numero di argomenti
    if (argc < 2) {
        printf("main: less than 2 arguments");
        exit(EXIT_FAILURE);
    }

    char *mainPID = calloc(1, sizeof(char)), Pnumber;

    sprintf(mainPID, "%d", getpid());

    signal(SIGCONT, SIGCONT_handler);
    printf("main: start P\n");

    /*si avviano i 3 processi p: Ad ogni p viene passato la modalità di esecuzione, Pnumber che specifica quale processo p deve
    essere eseguito e infine il pid del main. Il main dovrà aspettare,tramite la pause(), il segnale dal processo appena creato per
    andare avanti*/

    for (int NP = 1; NP <= 3; NP++) {
        if (!fork()) {
            Pnumber = NP + 48;
            int e = execl("./p", "p", argv[1], &Pnumber, mainPID, (char *) NULL);
            if (e == -1) {
                perror("main: execl");
                exit(EXIT_FAILURE);
            }
        }
        pause();
    }

    int pid_decision = fork();

    //si crea il processo Decision Function
    if (pid_decision == 0) {
        printf("main: start DF\n");
        execl("./decision_function", "decision_function", (char *) NULL);
    } else {
        // il main esegue il codice di Input Manager
        printf("main: start IM\n");
        execl("./input_manager", "input_manger", argv[2], (char *) NULL);
    }
}
