#include "../lib/ipc.h"

void createPIPE(char *path[], int nrelements) {
    for (int i = 0; i < nrelements; i++) {
        unlink(path[i]);
        int mkresult;
        if ((mkresult = mknod(path[i], S_IFIFO, DEFAULT)) == -1) {
            char message[100];
            sprintf(message, "open %s", path[i]);
            perror(message);
            exit(EXIT_FAILURE);
        }
        printf("IPC: mkresult = %d su %s", mkresult, path[i]);
        chmod(path[i], PERMISSIONPIPE);
    }

}

int *openPIPE(char *path[], int nrelements, int *flag) {
    int *fd = (int *) calloc(nrelements, sizeof(int));
    printf("nrelements = %d\n", nrelements);
    for (int i = 0; i < nrelements; i++) {
        printf("IPC: open (%d) %s with flag %d", i, path[i], flag[i]);
        if ((fd[i] = open(path[i], flag[i])) == -1) {
            char message[100];
            sprintf(message, "open %s", path[i]);
            perror(message);
            exit(EXIT_FAILURE);
        }
        printf(" with result %d\n", fd[i]);
    }
    return fd;
}