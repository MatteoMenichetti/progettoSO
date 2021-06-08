#include "../lib/ipc.h"

int initializationSOCKET(struct sockaddr_un *sockServer) {
    strcpy(sockServer->sun_path, SOCKADDR);
    sockServer->sun_family = AF_UNIX;
    unlink(SOCKADDR);
    int ssfd;
    if ((ssfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("server: socket");
        exit(EXIT_FAILURE);
    }

    if (bind(ssfd, (struct sockaddr *) sockServer, sizeof(*sockServer)) == -1) {
        perror("server: bind");
        exit(EXIT_FAILURE);
    }

    if (listen(ssfd, 1) == -1) {
        perror("server: listen");
        exit(EXIT_FAILURE);
    }

    return ssfd;
}

void acceptSOCKET(int *asfd) {
    struct sockaddr_un sockServer, socketClient;
    int ssfd = initializationSOCKET(&sockServer);
    unsigned int len = sizeof(socketClient);
    if ((*asfd = accept(ssfd, (struct sockaddr *) &socketClient, &len)) == -1) {
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
    chmod(PIPEADDR, 0777);
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
    int fdPipe, fpAppoggio = open(FILEADDR, O_CREAT | O_WRONLY | O_TRUNC, 0777), asfd;
    FILE *fpData = fopen(argv[0], "r");

    initializationPIPE();
    openPIPE(&fdPipe);
    acceptSOCKET(&asfd);

    fgets(buff, BUFSIZ, fpData);
    strncpy(buff, "\0", strlen(buff));

    int stringaScritta = 0;
    while (fgets(buff, BUFSIZ, fpData) != NULL) {
        //
        write(fdPipe, buff, strlen(buff));
        //
        write(asfd, buff, strlen(buff));
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