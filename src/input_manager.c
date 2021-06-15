#include "../lib/ipc.h"

int initializationSOCKET(struct sockaddr_un *sockServer) {
    int fd;

    strcpy(sockServer->sun_path, SOCKPATH);
    sockServer->sun_family = AF_UNIX;

    unlink(SOCKPATH);

    if ((fd = socket(AF_UNIX, SOCK_STREAM, DEFAULT)) == -1) {
        perror("IM: socket");
        exit(EXIT_FAILURE);
    }

    if (bind(fd, (struct sockaddr *) sockServer, sizeof(*sockServer)) == -1) {
        perror("IM: bind");
        exit(EXIT_FAILURE);
    }

    if (listen(fd, 1) == -1) {
        perror("IM: listen");
        exit(EXIT_FAILURE);
    }

    return fd;
}

void acceptSOCKET(int *sfd) {
    struct sockaddr_un sockServer, socketClient;
    int ssfd = initializationSOCKET(&sockServer);
    unsigned int len = sizeof(socketClient);

    if ((*sfd = accept(ssfd, (struct sockaddr *) &socketClient, &len)) == -1) {
        perror("server: accept");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("input_manager: numero argomenti insuff.\n");
        exit(EXIT_FAILURE);
    }
    char buff[BUFSIZ], *path= {PIPEPATH};
    int flag =O_WRONLY, fdPipe, fpAppoggio = open(FILEPATH,
                                                        O_CREAT | O_WRONLY |
                                                        O_TRUNC,
                                                        PERMISSIONFILE), sfd;
    FILE *fpData = fopen(argv[1], "r");

    printf("IM: create PIPE\n");

    createPIPE(PIPEPATH);

    printf("IM: open PIPE\n");

    fdPipe = openPIPE(path, flag);

    printf("IM: accept\n");
    acceptSOCKET(&sfd);

    fgets(buff, BUFSIZ, fpData);
    strncpy(buff, "\0", strlen(buff));

    while (fgets(buff, BUFSIZ, fpData) != NULL) {
        printf("IM: write for P\n");
        //
        write(fdPipe, buff, strlen(buff));
        //
        write(sfd, buff, strlen(buff));
        //
        write(fpAppoggio, buff, strlen(buff));
        fsync(fpAppoggio);
        //
        sleep(1);
        strncpy(buff, "\0", strlen(buff));
    }
    fclose(fpData);
    close(fpAppoggio);
    kill(0, SIGKILL);
}