#include "../lib/p.h"

void p3(int flag, int pid) {
    unlink(PIPEDP3);
    if (mknod(PIPEDP3, S_IFIFO, DEFAULT) == -1) {
        perror("P: mknod");
        exit(EXIT_FAILURE);
    }
    chmod(PIPEDP3, 0777);
    kill(pid, SIGCONT);
    int psfd;
    if ((psfd = open(PIPEDP3, O_WRONLY)) == -1) {
        perror("P3: open pipe");
        exit(EXIT_FAILURE);
    }
    FILE *fd = fopen(FILEADDR, "r+");


    if (fd == NULL) {
        perror("P3: open");
        exit(EXIT_FAILURE);
    }

    char buff[BUFSIZ];
    char *token = (char *) malloc(sizeof(char));
    int s = 0;
    int res = 0;

    while (0 == 0) {
        if (fgets(buff, sizeof(buff), fd)) {
            res += strlen(buff);
            token = splitP2(buff);
            s = sum(token, 0);
            if (flag == ACTIVE_FAILURE) { errsum(&s, 30); }
            if (write(psfd, &s, sizeof(s)) == -1) {
                perror("P1: write");
                exit(EXIT_FAILURE);
            }
            printf("Inviato P3: %d \n", s);
        }
        fseek(fd, res, SEEK_SET);
    }
}
