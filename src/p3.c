#include "../lib/p.h"

void p3(int modality, int psfd) {

    FILE *fd = fopen(PIPEDECISIONADDR, "r");
    int fd1 = open("../file.txt", O_RDONLY);

    if (fd == NULL) {
        perror("P3: open");
        exit(EXIT_FAILURE);
    }
    char buff[BUFSIZ];


    while (0 == 0) {
        fgets(buff, sizeof(buff), fd);
        splitP2(buff, psfd);

        sleep(1);
    }
}