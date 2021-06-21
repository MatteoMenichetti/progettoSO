#include "../lib/common.h"

void SIGCONT_handler() { /* do nothing */ }

int main(int argc, char *argv[]) {

    //si controlla che siano passati il giusto numero di argomenti
    if (argc < 3) {
        printf("main: less than 3 arguments\n");
        exit(EXIT_FAILURE);
    }

    char *mainPID = calloc(1, sizeof(char)), Pnumber;
    sprintf(mainPID, "%d", getpid());
    signal(SIGCONT, SIGCONT_handler);
    printf("main: start P\n");

    /*si avviano i 3 processi p: Ad ogni p viene passato la modalità di esecuzione, Pnumber che specifica quale processo p deve 
    essere eseguito e infine il pid del main. Il main dovrà aspettare,tramite la pause(), il segnale dal processo appena creato per 
    andare avanti. L'invocazione della funzione pause() è dovuta alla creazione delle pipe neccessarie per la comunicazione tra
    i p e il decision_function (se non sono state create non è possibile comunicare) e quindi per evitare errori durante l'apertura,
     da parte del decision_function, delle pipe la sua creazione sarà posticipata fin quando le pipe non sono state create*/

    for (int NP = 0; NP < 3; NP++) {
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
        printf("main: start decision_function\n");
        execl("./decision_function", "decision_function", (char *) NULL);
    } else {
        // il main esegue il codice di Input Manager
        printf("main: start input_manager\n");
        execl("./input_manager", "input_manger", argv[2], (char *) NULL);
    }
}
