#include "../lib/p.h"

void p1(int flag, int pid) {
    unlink(PIPEDP1);
    if (mknod(PIPEDP1, S_IFIFO, DEFAULT) == -1) {
        perror("P: mknod");
        exit(EXIT_FAILURE);
    }
    chmod(PIPEDP1, 0777);


    int kills = kill(pid, SIGCONT);

    int psfd = 0;
    if ((psfd = open(PIPEDP1, O_WRONLY)) == -1) {
        perror("P1: open pipe");
        exit(EXIT_FAILURE);
    }

    int pfd = open(PIPEADDR, O_RDONLY);

    char buff[BUFSIZ];
    int s = 0, r = 0;
    while (0 == 0) {
        r = read(pfd, buff, sizeof(buff));
        if (r == 0) {
            continue;
        }

        if (r == -1) {
            perror("P1: read su pipe");
            exit(EXIT_FAILURE);
        }

        splitP1(buff, &s);

        if (flag == ACTIVE_FAILURE)errsum(&s, 10);

        printf("P1: invio a DF %d\n", s);
        if (write(psfd, &s, sizeof(s)) == -1) {
            perror("P1: write");
            exit(EXIT_FAILURE);
        }
        strncpy(buff, "\0", r);

        s = 0;
    }
}

void splitP1(char *buff, int *s) {
    char *token;
    token = strtok(buff, delim);
    printf("P1: token =  %s", buff);
    do {
        *s += sum(token, 0);
    } while ((token = strtok(NULL, delim)) != NULL);
}