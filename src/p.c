#include "../lib/p.h"
#include <time.h>

int main(int argc, int *argv[]) {
    if (argc < 3) {
        printf("P: argomenti non sufficienti");
        exit(0);
    }
    int modality = 0;
    if (!strcmp(ENABLE, argv[1]))modality = 1;

    int pfd = open(PIPEDECISIONADDR, O_RDWR);
    if (*argv[2] == 1) {
        p1(modality, pfd);
    }
    if (*argv[2] == 2) {
        p2(modality, pfd);
    }
    if (*argv[2] == 3) {
        p3(modality, pfd);
    }
    return 0;
}

void init() {
    if (!unlink(PIPEDECISIONADDR)) {
        if (mknod(PIPEDECISIONADDR, S_IFIFO, DEFAULT) == -1) {
            perror("P: mknod");
            exit(0);
        }
    } else {
        perror("P: unlink");
        exit(0);
    }
}

int sum(char *token, int start) {
    int s = 0;
    for (int l = start; l < strlen(token); l++)
        s += *(token + l);
    return s;
}
