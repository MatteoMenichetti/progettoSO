#include "../lib/ipc.h"

int main(int argc, int *argv[]) {
    if (argc < 3) {
        printf("P: argomenti non sufficienti");
        exit(0);
    }

    if (*argv[2] == 1) {
            p1(*argv[1]);
    }
    if (*argv[2] == 2) {
            p2(*argv[1]);
    }
    if (*argv[2] == 3) {
            p3(*argv[1]);
    }
    return 0;
}

void p1(int mode) {
    int pfd = open(PADDR, O_RDONLY);
    char buff[100];
    while (0 == 0) {
        read(pfd, buff, 100)
        printf("P1: legge = %s", buff);
    }
}