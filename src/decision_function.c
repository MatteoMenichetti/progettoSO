#include "../lib/ipc.h"
#include <stdlib.h>

#define LOGPOS "system_log"
#define LOGVAL 0
#define P1 1
#define P2 2
#define P3 3

void opens(int *fd) {

    if ((fd[LOGVAL] = open(LOGPOS, O_WRONLY) == -1)) {
        perror("DF: open");
        exit(EXIT_FAILURE);
    }
    if ((fd[P1] = open(PIPEDP1, O_RDONLY) == -1)) {
        perror("DF: open");
        exit(EXIT_FAILURE);
    }
    if ((fd[P2] = open(PIPEDP2, O_RDONLY) == -1)) {
        perror("DF: open");
        exit(EXIT_FAILURE);
    }
    if ((fd[P3] = open(PIPEDP3, O_RDONLY) == -1)) {
        perror("DF: open");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    int fd[4];
    char buff[BUFSIZ];
    opens(fd);
    while (0 == 0) {
        for (int i = 0; i < 3; i++) {
            printf("DF: eseguo la read\n");
            if (read(fd[P1], (buff + i), sizeof(int)) == -1) {
                perror("DF: read");
                exit(EXIT_FAILURE);
            }
            printf("DF: buff[i] = %c\n", buff[i]);
        }
    }
}