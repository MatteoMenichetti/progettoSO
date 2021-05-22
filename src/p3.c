#include "../lib/p.h"

void p3(int modality, int psfd) {

    FILE *fd = fopen(PIPEDECISIONADDR, "r");

    if (fd == NULL) {
        perror("P3: open");
        exit(EXIT_FAILURE);
    }
    char buff[BUFSIZ];

    while (0 == 0) {
        while(fgets(buff, sizeof(buff), fd)==EOF);
        splitP2(buff, psfd);
    }
}