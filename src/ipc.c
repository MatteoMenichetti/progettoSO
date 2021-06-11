#include "../lib/ipc.h"

void createPIPE(char *path[], int nrelements) {
    for (int i = 0; i < nrelements; ++i) {
        unlink(path[i]);
        if ((mknod(path[i], S_IFIFO, DEFAULT)) == -1) {
            perror("watchdog: mknod");
            exit(EXIT_FAILURE);
        }
        chmod(path[i], PERMISSIONPIPE);
    }

}

int *openPIPE(char *path[], int nrelements, int *flag) {
    int *fd = (int *) calloc(nrelements, sizeof(int));
    for (int i = 0; i < nrelements; i++)
        if ((fd[i] = open(path[i], flag[i])) == -1) {
            char message[100];
            sprintf(message, "open %s", path[i]);
            perror(message);
            exit(EXIT_FAILURE);
        }
    return fd;
}