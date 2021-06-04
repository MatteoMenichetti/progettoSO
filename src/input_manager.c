#include "../lib/ipc.h"
#include <signal.h>

int initializationSOCKET(struct sockaddr_un *sockServer) {
    strcpy(sockServer->sun_path, SOCKADDR);
    sockServer->sun_family = AF_UNIX;
    unlink(SOCKADDR);
    int ssfd;
    if ((ssfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT)) == -1) {
        perror("IM: socket");
        exit(EXIT_FAILURE);
    }

    printf("IM: ssfd = %d\n", ssfd);

    if (bind(ssfd, (struct sockaddr *) sockServer, sizeof(*sockServer)) == -1) {
        perror("IM: bind");
        exit(EXIT_FAILURE);
    }

    printf("IM: bind eseguita\n");

    if (listen(ssfd, 1) == -1) {
        perror("IM: listen");
        exit(EXIT_FAILURE);
    }

    printf("IM: listen eseguita\n");
    return ssfd;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("IM: numero argomenti non suff.");
        exit(EXIT_FAILURE);
    }
    int pid;
    char c;
    printf("IM: avvio i tre P\n");
    printf("IM: argv[2] = %s\n", argv[2]);
    for (int NP = 1; NP <= 3; NP++) {
        if (!fork()) {
            c = NP + 48;
            int e = execl("./p", argv[1], argv[2], &c, (char *) NULL);
            printf("IM: execl = %d\n", e);
            if (e == -1) {
                perror("IM: execl");
                exit(EXIT_FAILURE);
            }
        }
    }

    printf("IM: avviati\n");

    char buff[BUFSIZ];
    int fpPipe;
    FILE *fpData = fopen(argv[2], "r");
    int fpAppoggio = open(FILEADDR, O_WRONLY | O_CREAT | O_TRUNC, 0777);

    chmod(FILEADDR, 0777);

    unlink(PIPEADDR);
    if (mknod(PIPEADDR, S_IFIFO, DEFAULT) == -1) {
        perror("IM: PIPEADDR");
        exit(EXIT_FAILURE);
    }
    chmod(PIPEADDR, 0777);

    printf("IM prima della open\n");

    fpPipe = open(PIPEADDR, O_WRONLY);
    if (fpPipe == -1) {
        perror("IM: open");
        exit(EXIT_FAILURE);
    }
    printf("IM: Sono dopo la open\n");

    struct sockaddr_un sockServer, socketClient;
    int ssfd = initializationSOCKET(&sockServer);
    int asfd;
    unsigned int len;
    len = sizeof(socketClient);
    printf("IM: eseguo la accept\n");
    if ((asfd = accept(ssfd, (struct sockaddr *) &socketClient, &len)) == -1) {
        perror("IM: accept");
        exit(EXIT_FAILURE);
    }

    printf("IM: accept eseguita\n");

    fgets(buff, BUFSIZ, fpData);
    strncpy(buff, "\0", strlen(buff));

    while (fgets(buff, BUFSIZ, fpData) != NULL) {
        printf("IM: scrivo %s\n", buff);
        write(fpAppoggio, buff, strlen(buff));
        fsync(fpAppoggio);
        write(fpPipe, buff, strlen(buff));
        write(asfd, buff, strlen(buff));
        sleep(10);
        strncpy(buff, "\0", strlen(buff));
    }
    fclose(fpData);
    close(fpAppoggio);
    close(asfd);
    kill(0, SIGKILL);
}