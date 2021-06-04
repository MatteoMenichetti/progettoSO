#include "../lib/p.h"

#define INT_ERR srand(time(NULL))

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("P: argomenti non sufficienti");
        exit(EXIT_FAILURE);
    }

    int FLAG = 0;
    printf("P: argv[0] =  %s, argv[1] = %s", argv[0], argv[1]);
    if ((strcmp(ENABLE, argv[0])) == 0) {
        INT_ERR;
        FLAG = 1;
    }
    if (atoi(argv[1]) == P1) {
        if (!fork()) {
            printf("P: ESECUZIONE P1\n");
            p1(FLAG);
        }
    }
    if (atoi(argv[1]) == P2) {
        if (!fork()) {
            printf("P: ESECUZIONE P2\n");
            p2(FLAG);
        }
    }
    if (atoi(argv[1]) == P3) {
        if (!fork()) {
            printf("P: ESECUZIONE P3\n");
            p3(FLAG);
        }
    }
    return 0;
}

int sumFromFirst(char *token) {
    int s = 0;
    for (int l = 0; l < strlen(token); l++)
        s += *(token + l);
    return s;
}

int sumFromLast(char *token) {
    int s = 0;
    for (int l = strlen(token); l >= 0; l--)
        s += *(token + l);
    return s;
}

int sum(char *token, int start) {
    if (start == 0)return sumFromFirst(token);
    return sumFromLast(token);
}

void errsum(int *s, int value) {
    if (ERR == EVENT)*s += value;
}