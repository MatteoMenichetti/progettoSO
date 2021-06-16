#include "../lib/p.h"

/*void p1(int modality, int pid) {
    int flag[1] = {O_WRONLY};
    char *path[1] = {PIPEDP1PATH};

    printf("P1: creazione PIPEDP1\n");
    createPIPE(path, 1);

    int kills = kill(pid, SIGCONT);

    printf("P1: open PIPEDP1\n");
    int psfd = *openPIPE(path, 1, flag);

    int pfd = open(PIPEPATH, O_RDONLY);

    char buff[BUFSIZ];
    int s = 0, r = 0;
    while (0 == 0) {
        if((r = read(pfd, buff, sizeof(buff)))==-1) {
            perror("P1: read su pipe");
            exit(EXIT_FAILURE);
        }
        printf("P1: splitP1\n");
        splitP1(buff, &s);

        if (modality == ACTIVE_FAILURE)errsum(&s, 10);

        printf("P1: invio a DF %d\n", s);
        if (write(psfd, &s, sizeof(s)) == -1) {
            perror("P1: write");
            exit(EXIT_FAILURE);
        }
        strncpy(buff, "\0", r);

        s = 0;
    }
}*/
void p1(int modality, int pid) {
    createPIPE(PIPEDP1PATH);

    kill(pid, SIGCONT);

    int flags[] = {O_WRONLY, O_RDONLY}, fd[2], s = 0;ssize_t r = 0;
    char *paths[] = {PIPEDP1PATH, PIPEPATH}, buff[BUFSIZ];

    for (int i = 0; i < 2; i++)
        fd[i] = openPIPE(paths[i], flags[i]);
    printf("P1: fd[0] = %d\n", fd[0]);//eliminare
    printf("P1: fd[1] = %d\n", fd[1]);//eliminare

    while (0 == 0) {
        if ((r = read(fd[1], buff, sizeof(buff))) == -1) {
            perror("P1: read on pipe");
            exit(EXIT_FAILURE);
        }

        splitP1(buff, &s);
        if (modality == ACTIVE_FAILURE)errsum(&s, 10);


        printf("P1: send to DF %d\n", s);
        if (write(fd[0], &s, sizeof(s)) == -1) {
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