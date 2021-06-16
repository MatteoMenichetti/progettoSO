#include "../lib/p.h"

void p3(int modality, int pid) {
    createPIPE(PIPEDP3PATH);

    kill(pid, SIGCONT);

    int psfd, flag = O_WRONLY, s = 0;
    unsigned long res = 0;

    char *path = {PIPEDP3PATH}, buff[BUFSIZ], *token = (char *) malloc(sizeof(char));

    printf("P3: open PIPEDP3\n");
    psfd = openPIPE(path, flag);

    FILE *fd = fopen(FILEPATH, "r+");

    if (fd == NULL) {
        perror("P3: open");
        exit(EXIT_FAILURE);
    }

    while (0 == 0) {
        if (fgets(buff, sizeof(buff), fd)) {
            res += strlen(buff);

            printf("P3: splitP2\n");
            token = splitP2(buff);

            s = sum(token, 0);
            if (modality == ACTIVE_FAILURE)errsum(&s, 30);

            printf("P3: send to DF %d\n", s);
            if (write(psfd, &s, sizeof(s)) == -1) {
                perror("P3: write");
                exit(EXIT_FAILURE);
            }

            strncpy(buff, "\0", strlen(buff));
        }
        fseek(fd, res, SEEK_SET);
    }
}
