#include "../lib/ipc.h"

void createPIPE(char *pipe) {
    unlink(pipe);
    if (mknod(pipe, S_IFIFO, DEFAULT) == -1) {
        perror("IPC: mknod");
        exit(EXIT_FAILURE);
    }
    chmod(pipe, PERMISSIONPIPE);
}

int openPIPE(char path[], int flag) {
    int fd;

    if ((fd = open(path, flag)) == -1) {
        char message[100];
        sprintf(message, "open %s with result %d\n", path, fd);
        perror(message);
        exit(EXIT_FAILURE);
    }

    return fd;
}
