#include "../lib/p.h"
#include <time.h>

int main(int argc, int *argv[]) {
    if (argc < 3) {
        printf("P: argomenti non sufficienti");
        exit(0);
    }

    if (*argv[2] == 1) {
        p1(*argv[1], init());
    }
    if (*argv[2] == 2) {
        p2(*argv[1], init());
    }
    if (*argv[2] == 3) {
        p3(*argv[1], init());
    }
    return 0;
}



void init() {
    int csfd;
    if ((csfd = socket(AF_UNIX, SOCK_STREAM, DEF)) == -1) {
        perror("client: socket");
        exit(0);
    }
    return csfd;
}