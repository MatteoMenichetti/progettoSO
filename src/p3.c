#include "../lib/p.h"

void p3(int modality, int pid) {
    int flag[1] = {O_WRONLY};

    createPIPE((char **) PIPEDP3PATH, 1);

    kill(pid, SIGCONT);

    int psfd = openPIPE((char **) PIPEDP3PATH, 1, flag);

    FILE *fd = fopen(FILEPATH, "r+");

    if (fd == NULL) {
        perror("P3: open");
        exit(EXIT_FAILURE);
    }

    char buff[BUFSIZ], *token = (char *) malloc(sizeof(char));
    int s = 0, res = 0;

    while (0 == 0) {
        if (fgets(buff, sizeof(buff), fd)) {
            res += strlen(buff);
            token = splitP2(buff);
            s = sum(token, 0);
            if (modality == ACTIVE_FAILURE) { errsum(&s, 30); }
            if (write(psfd, &s, sizeof(s)) == -1) {
                perror("P1: write");
                exit(EXIT_FAILURE);
            }
            printf("Inviato P3: %d \n", s);
        }
        fseek(fd, res, SEEK_SET);
    }
}
