#include "../lib/ipc.h"


//questo metodo inizializza la socket, esegue la bind e la listen e restituisce il File descriptor della socket
int initializationSOCKET(struct sockaddr_un *sock_server) {
    int socket_server_fd;

    strcpy(sock_server->sun_path, SOCKPATH);
    sock_server->sun_family = AF_UNIX;

    unlink(SOCKPATH);

    if ((socket_server_fd = socket(AF_UNIX, SOCK_STREAM, DEFAULT)) == -1) {
        perror("input_manager: socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socket_server_fd, (struct sockaddr *) sock_server, sizeof(*sock_server)) == -1) {
        perror("input_manager: bind");
        exit(EXIT_FAILURE);
    }

    if (listen(socket_server_fd, 1) == -1) {
        perror("input_manager: listen");
        exit(EXIT_FAILURE);
    }

    return socket_server_fd;
}

// metodo che esegue l'accept della socket
void acceptSOCKET(int *asocket_server_fd) {
    struct sockaddr_un sock_server, socket_client;
    int socket_server_fd = initializationSOCKET(&sock_server);
    unsigned int len = sizeof(socket_client);

    if ((*asocket_server_fd = accept(socket_server_fd, (struct sockaddr *) &socket_client, &len)) == -1) {
        perror("input_manager: accept");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("input_manager: less than 2 arguments\n");
        exit(EXIT_FAILURE);
    }


    char buff[BUFSIZ], *path = {PIPEPATH};

    /* pipe_flag= modalità di apertura della pipe PIPEPATH
       fd_pipe= variabile in cui sarà inserito il file descriptor di PIPEPATH
       fd_share_file = file descriptor del FILEPATH (File da dove leggera P3)
       socket_server_fd = variabile in cui sarà inserito il file descriptor della socket SOCKPATH */

    int pipe_flag = O_WRONLY, fd_pipe, fd_share_file = open(FILEPATH,
                                                            O_CREAT | O_WRONLY |
                                                            O_TRUNC,
                                                            PERMISSIONFILE), socket_server_fd;
    //apertura del dataset.csv in lettura
    FILE *fp_data_set = fopen(argv[1], "r");

    createPIPE(PIPEPATH);

    acceptSOCKET(&socket_server_fd);

    fd_pipe = openPIPE(path, pipe_flag);

    //ignora prima linea
    fgets(buff, BUFSIZ, fp_data_set);
    strncpy(buff, "\0", strlen(buff));

    while (fgets(buff, BUFSIZ, fp_data_set) != NULL) {
        printf("input_manager: write for P\n");
        //scrittura su pipe
        write(fd_pipe, buff, strlen(buff));
        //scrittura su socket
        write(socket_server_fd, buff, strlen(buff));
        //scrittura su file
        write(fd_share_file, buff, strlen(buff));
        fsync(fd_share_file);
        //
        sleep(1);
        strncpy(buff, "\0", strlen(buff)); //necessario per invalidare il buffer estratto da dataset.csv
    }

    //chiusura file
    fclose(fp_data_set);
    close(fd_share_file);
    close(fd_pipe);

    printf("input_manager: end of file (kill all process)\n");
    kill(0, SIGKILL);
}