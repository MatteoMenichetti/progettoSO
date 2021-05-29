#include "../lib/ipc.h"
#include <signal.h>

int initializationSOCKET(struct sockaddr_un *sockServer) {
    strcpy(sockServer->sun_path, SOCKADDR);
    sockServer->sun_family = AF_UNIX;
    unlink(SOCKADDR);
    int ssfd;
    if ((ssfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("server: socket");
        exit(EXIT_FAILURE);
    }

    printf("server: ssfd = %d\n", ssfd);

    if (bind(ssfd, (struct sockaddr *) sockServer, sizeof(*sockServer)) == -1) {
        perror("server: bind");
        exit(EXIT_FAILURE);
    }

    printf("bind eseguita\n");

    if (listen(ssfd, 1) == -1) {
        perror("server: listen");
        exit(EXIT_FAILURE);
    }

    printf("listen eseguita\n");
    return ssfd;
}

int main(int argc, char *argv[]) {
    char buff[BUFSIZ];

    int fpPipe;
    FILE *fpData = fopen("../reduceDATAset.csv", "r");
    int fpAppoggio = open(FILEADDR, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    chmod(FILEADDR, 0777);

    unlink(PIPEADDR);
    if (mknod(PIPEADDR, S_IFIFO, DEFAULT) == -1) {
        perror("Input manager: PIPEADDR");
        exit(EXIT_FAILURE);
    }
    chmod(PIPEADDR, 0777);

    printf("Input Manager prima della open\n");
    fpPipe = open(PIPEADDR, O_WRONLY);
    if (fpPipe == -1) {
        perror("Input: open");
        exit(EXIT_FAILURE);
    }
    printf("Sono dopo la open\n");
    /* struct sockaddr_un sockServer, socketClient;
     int ssfd = initializationSOCKET(&sockServer);
     int asfd;
     unsigned int len;
     len = sizeof(socketClient);
     printf("IM: eseguo la accept\n");
     if ((asfd = accept(ssfd, (struct sockaddr *) &socketClient, &len)) == -1) {
         perror("server: accept");
         exit(EXIT_FAILURE);
     }*/

    //inserire fork

    printf("accept eseguita\n");

    fgets(buff, BUFSIZ, fpData);
    strncpy(buff, "\0", strlen(buff));

    int stringaScritta = 0;
    while (fgets(buff, BUFSIZ, fpData) != NULL) {
        printf("IM: scrivo %s\n", buff);
        write(fpAppoggio, buff, strlen(buff));
        fsync(fpAppoggio);
        printf("Stringa scritta in file di appoggio %s \n", buff);
        write(fpPipe, buff, strlen(buff));
        //write(asfd, buff, strlen(buff));
        sleep(10);
        strncpy(buff, "\0", strlen(buff));
    }
    fclose(fpData);
    close(fpAppoggio);
    kill(0, SIGKILL);
}