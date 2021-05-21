#include "../lib/ipc.h"
#include <stdlib.h>

void main (void){
    struct sockaddr_un sockServer, socketClient;
    strcpy(sockServer.sun_path, SOCKDECISIONADDR);
    sockServer.sun_family = AF_UNIX;

    unlink(SOCKDECISIONADDR);
    int ssfd;
    if ((ssfd = socket(AF_UNIX, SOCK_STREAM, DEF)) == -1) {
        perror("decision_function: socket");
        exit(0);
    }

    if (bind(ssfd, (struct sockaddr *) &sockServer, sizeof(sockServer)) == -1) {
        perror("decision_function: bind");
        exit(0);
    }

    if (listen(ssfd, 3) == -1) {
        perror("decision_function: listen");
        exit(0);
    }
    int asfd, nrchar;
    char str[100];
    int len;
    struct sockaddr cast;
    while (0 == 0) {
        len = sizeof(socketClient);
        if ((asfd = accept(ssfd, (struct sockaddr *) &socketClient, &len)) == -1) {
            perror("decision_function: accept");
            break;
        }
        if (fork() == 0) {
            nrchar = read(asfd, str, sizeof(str));
            printf("server: ricevuto = %s, nrchar = %d\n", str, nrchar);
            str[strlen(str)] = 'S';
            write(asfd, str, strlen(str));
            close(asfd);
        }
    }
    close(ssfd);
    unlink(ADDRSOCK);
}