#include "../lib/ipc.h"

int initializationSOCKET(struct sockaddr_un *sockServer) {
    int fd;
    
    strcpy(sockServer->sun_path, SOCKADDR);
    sockServer->sun_family = AF_UNIX;
    
    unlink(SOCKADDR);
    
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

void initializationPIPE() {
    
    unlink(PIPEADDR);
    
    if (mknod(PIPEADDR, S_IFIFO, DEFAULT) == -1) {
        perror("Input manager: PIPEADDR");
        exit(EXIT_FAILURE);
    }
    chmod(PIPEADDR, PERMISSION);
}

void openPIPE(int *fdPipe) {
    *fdPipe = open(PIPEADDR, O_WRONLY);
    if (*fdPipe == -1) {
        perror("Input: open");
        exit(EXIT_FAILURE);
    }

}

int main(int argc, char *argv[]) {

    char buff[BUFSIZ];
    int fdPipe, fpAppoggio = open(FILEADDR, O_CREAT | O_WRONLY | O_TRUNC, PERMISSION), sfd;
    FILE *fpData = fopen(argv[0], "r");

    initializationPIPE();
    openPIPE(&fdPipe);
    acceptSOCKET(&sfd);

    fgets(buff, BUFSIZ, fpData);
    strncpy(buff, "\0", strlen(buff));

    while (fgets(buff, BUFSIZ, fpData) != NULL) {
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