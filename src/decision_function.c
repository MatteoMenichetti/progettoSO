#include "../lib/ipc.h"
#include <stdlib.h>

int main(void) {
    int pfd;
    if ((pfd = open(PIPEDECISIONADDR, O_RDONLY) == -1)) {
        perror("DF: open");
        exit(EXIT_FAILURE);
    }

    char buff[BUFSIZ];
    while (0 == 0) {
        for (int i = 0; i < 3; i++) {
            printf("DF: eseguo la read\n");
            if (read(pfd, (buff + i), sizeof(int)) == -1) {
                perror("DF: read");
                exit(EXIT_FAILURE);
            }
            printf("DF: buff[i] = %c\n", buff[i]);
        }
    }
}