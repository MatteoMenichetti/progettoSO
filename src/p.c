#include "../lib/p.h"
#include <time.h>

int main(int argc, int *argv[]) {
    if (argc < 3) {
        printf("P: argomenti non sufficienti");
        exit(0);
    }

    if (*argv[2] == 1) {
        p1(argv[1], fd);
    }
    if (*argv[2] == 2) {
        p2(*argv[1], fd);
    }
    if (*argv[2] == 3) {
        p3(*argv[1], fd);
    }
    return 0;
}

int init() {
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