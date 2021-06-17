#include "../lib/ipc.h"

//questo metodo inizializza la socket, esegue la bind e la listen e restituisce il File descriptor della socket
int initializationSOCKET(struct sockaddr_un *sockServer) {
    int socket_server_fd;

    strcpy(sockServer->sun_path, SOCKPATH);
    sockServer->sun_family = AF_UNIX;

    unlink(SOCKPATH);

    if ((socket_server_fd = socket(AF_UNIX, SOCK_STREAM, DEFAULT)) == -1) {
        perror("input_manager: socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socket_server_fd, (struct sockaddr *) sockServer, sizeof(*sockServer)) == -1) {
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
    struct sockaddr_un sockServer, socketClient;
    int socket_server_fd = initializationSOCKET(&sockServer);
    unsigned int len = sizeof(socketClient);

    if ((*asocket_server_fd = accept(socket_server_fd, (struct sockaddr *) &socketClient, &len)) == -1) {
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

    /* pipe_Flag= modalità di apertura della pipe PIPEPATH
    fd_pipe= variabile in cui sarà inserito il file descriptor di PIPEPATH
    fd_Share_File= file descriptor del FILEPATH (File da dove leggera P3)
    socket_server_fd= variabile in cui sarà inserito il file descriptor della socket SOCKPATH */

    int pipe_Flag = O_WRONLY, fd_Pipe, fd_Share_File = open(FILEPATH,
                                                            O_CREAT | O_WRONLY |
                                                            O_TRUNC,
                                                            PERMISSIONFILE), socket_server_fd;

    //apertura del dataset in lettura
    FILE *fpDataSet = fopen(argv[1], "r");

    printf("input_manager: create PIPE\n");

    createPIPE(PIPEPATH);

    printf("input_manager: accept\n");
    acceptSOCKET(&socket_server_fd);

    printf("input_manager: open PIPE\n");

    fd_Pipe = openPIPE(path, pipe_Flag);

    fgets(buff, BUFSIZ, fpDataSet);
    strncpy(buff, "\0", strlen(buff));

    while (fgets(buff, BUFSIZ, fpDataSet) != NULL) {
        printf("input_manager: write for P\n");
        //scrittura su pipe
        write(fd_Pipe, buff, strlen(buff));
        //scrittura su socket
        write(socket_server_fd, buff, strlen(buff));
        //scrittura su file
        write(fd_Share_File, buff, strlen(buff));
        fsync(fd_Share_File);
        //
        sleep(1);
        strncpy(buff, "\0", strlen(buff));
    }

    //chiusura file
    fclose(fpDataSet);
    close(fd_Share_File);
    close(fdPipe);

    printf("input_manager: end of file (kill all process)\n");
    kill(0, SIGKILL);
}