#include "../lib/p.h"

void p3(int flag, int pid) {
    printf("P3: eseguo unlink\n");

    unlink(PIPEDP3);
    if (mknod(PIPEDP3, S_IFIFO, DEFAULT) == -1) {
        perror("P3: mknod");
        exit(EXIT_FAILURE);
    }
    chmod(PIPEDP3, 0777);

    int psfd;
    printf("P1: invio SIGCONT a %d\n", pid);
    kill(pid, SIGCONT);
    printf("P3: apro PIPEDP3\n");
    if ((psfd = open(PIPEDP3, O_WRONLY)) == -1) {
        perror("P3: open pipe");
        exit(EXIT_FAILURE);
    }

    printf("P3: eseguo fopen\n");
    FILE *fd = fopen(FILEADDR, "r+");

    printf("P3: fopen eseguita\n");
    if (fd == NULL) {
        perror("P3: open");
        exit(EXIT_FAILURE);
    }
    printf("P3: sono prima del buffer \n");
    char buff[BUFSIZ];
    char *token = (char *) calloc(1, sizeof(char));
    printf("P3: sono prima del while \n");

    int s, res = 0;

    while (0 == 0) {
        if (fgets(buff, sizeof(buff), fd)) {
            res += strlen(buff);
            token = splitP2(buff);
            s = sum(token, 0);
            if (flag == ACTIVE_FAILURE)errsum(&s, 30);
            printf("somma: %d \n", s);
            if (write(psfd, &s, sizeof(s)) == -1) {
                perror("P3: write");
                exit(EXIT_FAILURE);
            }
            printf("Inviato: %d \n", s);
        }
        fseek(fd, res, SEEK_SET);
    }
}