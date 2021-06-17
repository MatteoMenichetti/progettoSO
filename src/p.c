#include "../lib/p.h"

#define INT_ERR srand(time(NULL))

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("P: less than 3 arguments");
        exit(EXIT_FAILURE);
    }

    int flag = 0, pid = atoi(argv[3]);

    if ((strcmp(argv[1], ENABLE)) == 0) {
        INT_ERR;
        flag = 1;
    }
    char cPnumebr;
    strncpy(&cPnumebr, argv[2], 1);
    int Pnumber = atoi((const char *)&cPnumebr);

    if (Pnumber == P1) {
        printf("ESECUZIONE P1\n");
        p1(flag, pid);
    }
    if (Pnumber == P2) {
        printf("ESECUZIONE P2\n");
        p2(flag, pid);
    }
    if (Pnumber == P3) {
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

int sum(char *token, unsigned long start) {
    if (start == 0)return sumFromFirst(token);
    return sumFromLast(token);
}

void errsum(int *s, int value) {
    if ((ERR == EVENT))*s += value;
}