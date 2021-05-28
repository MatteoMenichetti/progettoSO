#include "../lib/p.h"

#define INT_ERR srand(time(NULL))

void initializationPIPE() {
    printf("P: eseguo unlink\n");

    if (mknod(PIPEDP1, S_IFIFO, DEFAULT) == -1) {
        perror("P: mknod");
        exit(EXIT_FAILURE);
    }
    printf("P: eseguo unlink\n");

    if (mknod(PIPEDP2, S_IFIFO, DEFAULT) == -1) {
        perror("P: mknod");
        exit(EXIT_FAILURE);
    }

    printf("P: eseguo unlink\n");

    if (mknod(PIPEDP3, S_IFIFO, DEFAULT) == -1) {
        perror("P: mknod");
        exit(EXIT_FAILURE);

    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("P: argomenti non sufficienti");
        exit(0);
    }
    initializationPIPE();
    if (!strcmp(ENABLE, argv[1])) {
        INT_ERR;
#define ERR rand() % (10) + 1;}
        int pfd[3] = {open(PIPEDP1, O_WRONLY), open(PIPEDP2, O_WRONLY), open(PIPEDP3, O_WRONLY)};
        if (*argv[2] == 1) {
            p1(pfd[0]);
        }
        if (*argv[2] == 2) {
            p2(pfd[1]);
        }
        if (*argv[2] == 3) {
            p3(pfd[2]);
        }
        return 0;
    }

}

int sumFromFirst(char *token, int start) {
    int s = 0;
    for (int l = start; l < strlen(token); l++)
        s += *(token + l);
    return s;
}

int sumFromLast(char *token, int start) {
    int s = 0;
    for (int l = start; l >= 0; l--)
        s += *(token + l);
    return s;
}

int sum(char *token) {
    int start = 0;
#ifdef LAST
    start= LAST;
#endif
    if (start == strlen(token)) {
        return sumFromLast(token, start);
    } else return sumFromFirst(token, start);
}