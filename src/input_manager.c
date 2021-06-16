#include "../lib/ipc.h"

int initializationSOCKET(struct sockaddr_un *sockServer) {
    int sfd;

    strcpy(sockServer->sun_path, SOCKPATH);
    sockServer->sun_family = AF_UNIX;

    unlink(SOCKPATH);

    if ((sfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT)) == -1) {
        perror("input_manager: socket");
        exit(EXIT_FAILURE);
    }

    if (bind(sfd, (struct sockaddr *) sockServer, sizeof(*sockServer)) == -1) {
        perror("input_manager: bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sfd, 1) == -1) {
        perror("input_manager: listen");
        exit(EXIT_FAILURE);
    }

    return sfd;
}

//asfd = anonymous socket fd
void acceptSOCKET(int *asfd) {
    struct sockaddr_un sockServer, socketClient;
    int ssfd = initializationSOCKET(&sockServer);
    unsigned int len = sizeof(socketClient);

    if ((*asfd = accept(ssfd, (struct sockaddr *) &socketClient, &len)) == -1) {
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

    int pipeFlag = O_WRONLY, fdPipe, fdShareFile = open(FILEPATH,
                                                   O_CREAT | O_WRONLY |
                                                   O_TRUNC,
                                                        PERMISSIONFILE), sfd;

    FILE *fpDataSet = fopen(argv[1], "r");

    printf("input_manager: create PIPE\n");

    createPIPE(PIPEPATH);

    printf("input_manager: accept\n");
    acceptSOCKET(&sfd);

    printf("input_manager: open PIPE\n");

    fdPipe = openPIPE(path, pipeFlag);

    fgets(buff, BUFSIZ, fpDataSet);
    strncpy(buff, "\0", strlen(buff));

    while (fgets(buff, BUFSIZ, fpDataSet) != NULL) {
        printf("input_manager: write for P\n");
        //scrittura su pipe
        write(fdPipe, buff, strlen(buff));
        //scrittura su socket
        write(sfd, buff, strlen(buff));
        //scrittura su file
        write(fdShareFile, buff, strlen(buff));
        fsync(fdShareFile);
        //
        sleep(1);
        strncpy(buff, "\0", strlen(buff));
    }

    fclose(fpDataSet);
    close(fdShareFile);
    close(fdPipe);

    kill(0, SIGKILL);
}