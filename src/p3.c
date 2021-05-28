#include "../lib/p.h"

void p3(int psfd, int flag) {

    FILE *fd = fopen(FILEADDR, "r");

    if (fd == NULL) {
        perror("P3: open");
        exit(EXIT_FAILURE);
    }
    char buff[BUFSIZ];

    while (0 == 0) {
        while (fgets(buff, sizeof(buff), fd) == NULL);
        splitP2(buff, psfd, flag, 0, 30);
    }
}