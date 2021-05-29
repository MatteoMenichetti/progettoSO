#include "../lib/p.h"

void p3(int flag) {
    printf("P3: eseguo unlink\n");

    unlink(PIPEDP3);
    if (mknod(PIPEDP3, S_IFIFO, DEFAULT) == -1) {
        perror("P: mknod");
        exit(EXIT_FAILURE);
    }
    chmod(PIPEDP3, 0777);

    int psfd;
    /*if ((psfd = open(PIPEDP3, O_WRONLY))) {
        perror("P3: open pipe");
        exit(EXIT_FAILURE);
    }*/

    printf("P3: eseguo fopen\n");

    FILE *fd = fopen(FILEADDR, "r");

    if (fd == NULL) {
        perror("P3: open");
        exit(EXIT_FAILURE);
    }
    char buff[BUFSIZ];
    int s=0;
    while (0 == 0) {
        while (fgets(buff, sizeof(buff), fd) == NULL)usleep(500);
        printf("P3: buff = %s", buff);
        s=splitP2(buff/*, psfd*/, flag, 0, 30);
        /*if (write(pfddf, &s, sizeof(s)) == -1) {
        perror("P1: write");
        exit(EXIT_FAILURE);
    }*/
        strncpy(buff, "\0", strlen(buff));
    }
}