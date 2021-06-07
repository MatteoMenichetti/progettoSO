#include "../lib/p.h"

#define INT_ERR srand(time(NULL))

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("P: argomenti non sufficienti");
        exit(0);
    }

    int flag = 0, pid = atoi(argv[2]);

    if ((strcmp(argv[0], ENABLE)) == 0) {
        INT_ERR;
        flag = 1;
    }

    if (atoi(argv[1]) == P1) {
        printf("ESECUZIONE P1\n");
        p1(flag, pid);
    }
    if (atoi(argv[1]) == P2) {
        printf("ESECUZIONE P2\n");
        p2(flag, pid);
    }
    if (atoi(argv[1]) == P3) {
        printf("ESECUZIONE P3\n");
        p3(flag, pid);
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
    if ((ERR == EVENT))*s += value;
}