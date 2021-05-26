#include "../lib/ipc.h"

int main() {
    char buff[BUFSIZ];
    FILE *fpData, *fpAppoggio;
    int fpPipe;
    fpData = fopen("datasetPiccolo.txt", "r");
    fpAppoggio = fopen("fileDiAppoggio.txt", "w");
    fgets(buff, BUFSIZ, fpData);
    unlink(PIPEADDR);
    mkfifo(PIPEADDR, 0777);
    printf("Input Manager prima della open\n");
    do {
        fpPipe = open(PIPEADDR, O_WRONLY);
        if (fpPipe)
            sleep(1);
    } while (fpPipe == -1);
    if (fpPipe == -1) {
        perror("Input: open");
        exit(EXIT_FAILURE);
    }
    printf("Sono dopo la open");
    struct sockaddr_un sockServer, socketClient;
    strcpy(sockServer.sun_path, SOCKADDR);
    sockServer.sun_family = AF_UNIX;
    unlink(SOCKADDR);
    int ssfd;
    if ((ssfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("server: socket");
        exit(EXIT_FAILURE);
    }

    printf("server: ssfd = %d\n", ssfd);

    if (bind(ssfd, (struct sockaddr *) &sockServer, sizeof(sockServer)) == -1) {
        perror("server: bind");
        exit(EXIT_FAILURE);
    }

    if (listen(ssfd, 1) == -1) {
        perror("server: listen");
        exit(EXIT_FAILURE);
    }
    int asfd;
    char str[100];
    int len;
    len = sizeof(socketClient);
    if ((asfd = accept(ssfd, (struct sockaddr *) &socketClient, &len)) == -1) {
        perror("server: accept");
        exit(EXIT_FAILURE);
    }
    while (fgets(buff, BUFSIZ, fpData) != NULL) {
        int stringaScritta = fputs(buff, fpAppoggio);
        //printf("Esito fputs:%d",stringaScritta);
        printf("Stringa scritta in file di appoggio %s \n", buff);
        write(fpPipe, buff, strlen(buff));
        write(asfd, buff, strlen(buff));
        sleep(1);
    }
    fclose(fpData);
    fclose(fpAppoggio);
}