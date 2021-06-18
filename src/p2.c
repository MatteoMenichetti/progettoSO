#include "../lib/p.h"

// creo la socket per scambiare dati con Input Manager
int definesocket() {
    int client_socket_fd;
    if ((client_socket_fd = socket(AF_UNIX, SOCK_STREAM, DEFAULT)) == -1) {
        perror("P2: socket");
        exit(EXIT_FAILURE);
    }
    return client_socket_fd;
}

// connetto la socket di p2 con quella di Input Manager
void connecting(int client_socket_fd) {
    struct sockaddr_un sock_server;
    strcpy(sock_server.sun_path, SOCKPATH);
    sock_server.sun_family = AF_UNIX;
    while ((connect(client_socket_fd, (struct sockaddr *) &sock_server, sizeof(sock_server))) == -1) {
        perror("P2: connect");
        sleep(1);
    }
}

// metodo principale che determina il comportamento di P2
void p2(int modality, int main_pid) {
    printf("p2: start\n");
    // creo la pipe per comunicare con DEcision Function
    createPIPE(PIPEDP2PATH);

    // invio segnale al main
    kill(main_pid, SIGCONT);

    int fd_pipe_decision_p2, flag = O_WRONLY, client_socket_fd = definesocket(), line_sum = 0;
    char *path = PIPEDP2PATH, line[BUFSIZ], *line_splitted = (char *) calloc(1, sizeof(char));

    // apro la pipe per scambiare dati con Decision Function
    fd_pipe_decision_p2 = openPIPE(path, flag);

    connecting(client_socket_fd);

    while (0 == 0) {
        //leggo la riga del dataset passata da input manager attraverso la socket
        if ((read(client_socket_fd, line, sizeof(line))) == -1) {
            perror("P1: read from pipe");
            exit(EXIT_FAILURE);
        }

        line_splitted = splitP2(line);
        // faccio la somma dei caratteri delle riga senza le virgole
        line_sum = sum(line_splitted, strlen(line_splitted));

        // eseguo errsum se il fallimento è attivo
        if (modality == ACTIVE_FAILURE) errsum(&line_sum, 20);
        printf("P2: send to decision_function%d\n", line_sum);

        // scrivo la somma della riga nella pipe per passarla a Decision Function
        if (write(fd_pipe_decision_p2, &line_sum, sizeof(line_sum)) == -1) {
            perror("P2: write");
            exit(EXIT_FAILURE);
        }

        strncpy(line, "\0", strlen(line));
    }
}

// estraggo le virgole dalla riga letta 
char *splitP2(char *line) {
    int s = 0;
    char *splitted_line = (char *) calloc(1, sizeof(char));
    for (int i = 0; i < (strlen(line)); i++) {
        if (strncmp((line + i), DELIMITER, 1) != 0) { //se il carattere i-esimo è uguale al delimiter allora split è completato e si passa ad un altro token
            splitted_line = (char *) realloc(splitted_line, strlen(splitted_line) + 1);//viene rilocata la stringa aggiungendo il carattere i-esimo
            splitted_line[s] = line[i];
            s++;
        }
    }
    return splitted_line;
}