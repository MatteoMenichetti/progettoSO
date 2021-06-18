#include "../lib/p.h"

void p3(int modality, int main_pid) {
    printf("p3: start\n");

    // creo la pipe per comunicare con Decision Function
    createPIPE(PIPEDP3PATH);
    // invio un segnale al main
    kill(main_pid, SIGCONT);

    int fd_pipe_decision_p3, flag = O_WRONLY, line_sum = 0;
    unsigned long res = 0;
    char *path = {PIPEDP3PATH}, line[BUFSIZ], *line_splitted = (char *) malloc(sizeof(char));

    // apro la pipe per comunicare con Decision Function
    fd_pipe_decision_p3 = openPIPE(path, flag);
    // apro il file di appoggio per comunicare con Input Manager
    FILE *fd_share_file = fopen(FILEPATH, "r+");

    if (fd_share_file == NULL) {
        perror("P3: open");
        exit(EXIT_FAILURE);
    }

    while (0 == 0) {

        // leggo la riga del dataset, sul file di appoggio, inviata da Input Manager
        if (fgets(line, sizeof(line), fd_share_file)) {
            res += strlen(line);

            // estraggo la virgola dalla riga letta da Input Manager
            line_splitted = splitP2(line);

            // effettuo la somma dei caratteri della riga senza le virgole
            line_sum = sum(line_splitted, 0);
            // eseguo il metodo errsum se è attivo il fallimento
            if (modality == ACTIVE_FAILURE)errsum(&line_sum, 30);

            printf("P3: send to decision_function %d\n", line_sum);
            // scrivo la somma della riga nella pipe per passarla a Decision Function
            if (write(fd_pipe_decision_p3, &line_sum, sizeof(line_sum)) == -1) {
                perror("P3: write");
                exit(EXIT_FAILURE);
            }

            strncpy(line, "\0", strlen(line));
        }
        fseek(fd_share_file, res, SEEK_SET);
    }
}
