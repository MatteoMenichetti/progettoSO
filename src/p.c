#include "../lib/p.h"

#define INT_ERR srand(time(NULL))

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("P: argomenti non sufficienti");
        exit(0);
    }
    if ((ENABLE - argv[1])) {
        INT_ERR;
#define FLAG 1
    }
#ifndef FLAG
#define FLAG 0
#endif


    if (atoi(argv[2]) == P1) {
        printf("ESECIZIONE P1\n");
        p1(FLAG);
    }
    if (atoi(argv[2]) == P2) {
        printf("ESECIZIONE P1\n");
        p2(FLAG);
    }
    if (atoi(argv[2]) == P3) {
        printf("ESECIZIONE P3\n");
        p3(FLAG);
    }
    return 0;
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

int sum(char *token, int start) {
    if (start == strlen(token)) {
        return sumFromLast(token, start);
    } else return sumFromFirst(token, start);
}

void errsum(int *s, int value) {
    if (ERR == EVENT)*s += value;
}