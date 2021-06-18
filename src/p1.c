#include "../lib/p.h"

// metodo principale che determina il comportamento di P1
void p1(int modality, int main_pid) {
    printf("p1: start\n");
    // creo la pipe per comunicare con decision Function
    createPIPE(PIPEDP1PATH);

    //invio segnale al main
    kill(main_pid, SIGCONT);

    int flags[] = {O_WRONLY, O_RDONLY}, fd[2], line_sum = 0;
    ssize_t charsReaded = 0;
    char *paths[] = {PIPEDP1PATH, PIPEPATH}, line[BUFSIZ];

    // apro le pipe per scambiare dati con decision e input manager
    for (int i = 0; i < 2; i++)
        fd[i] = openPIPE(paths[i], flags[i]);

    while (0 == 0) {

        // legge la riga del dataset tramite la pipe da Input Manager
        if ((charsReaded = read(fd[1], line, sizeof(line))) == -1) {
            perror("P1: read on pipe");
            exit(EXIT_FAILURE);
        }

        splitP1(line, &line_sum);
        // attiva il fallimento se ACTIVE_FAILURE == 1 
        if (modality == ACTIVE_FAILURE)errsum(&line_sum, 10);

        printf("P1: send to decision_function %d\n", line_sum);
        // scrive la somma della riga sulla pipe per passare il valore alla Decision Function
        if (write(fd[0], &line_sum, sizeof(line_sum)) == -1) {
            perror("P1: write");
            exit(EXIT_FAILURE);
        }
        strncpy(line, "\0", charsReaded);

        line_sum = 0;
    }
}

// estrae la virgola dalla riga letta da Input Manager e fa la somma dei caratteri
void splitP1(char *line, int *line_sum) {
    char *splitted_line;
    splitted_line = strtok(line, DELIMITER);
    do {
        *line_sum += sum(splitted_line, 0);
    } while ((splitted_line = strtok(NULL, DELIMITER)) != NULL);
}