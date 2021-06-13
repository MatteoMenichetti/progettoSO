#include "../lib/p.h"

void p3(int modality, int pid) {
    int flag[1] = {O_WRONLY};
    char *path[1] = {PIPEDP3PATH};

    printf("P3: creazione PIPEDP3\n");
    createPIPE(path, 1);

    kill(pid, SIGCONT);

    printf("P3: open PIPEDP3\n");
    int psfd = *openPIPE(path, 1, flag);

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
            printf("P3: splitP2\n");
            token = splitP2(buff);
            s = sum(token, 0);
            if (modality == ACTIVE_FAILURE)errsum(&s, 30);
            if (write(psfd, &s, sizeof(s)) == -1) {
                perror("P3: write");
                exit(EXIT_FAILURE);
            }
            printf("P3: %d \n", s);
        }
        fseek(fd, res, SEEK_SET);
    }
}
