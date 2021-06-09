#include "../lib/p.h"

#define INT_ERR srand(time(NULL))

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("P: argomenti non sufficienti");
        exit(0);
    }

    int flag = 0, pid = atoi(argv[3]);

    if ((strcmp(argv[1], ENABLE)) == 0) {
        INT_ERR;
        flag = 1;
    }

    if (atoi(argv[2]) == P1) {
        printf("p: ESECUZIONE P1\n");
        p1(flag, pid);
    }
    if (atoi(argv[2]) == P2) {
        printf("p: ESECUZIONE P2\n");
        p2(flag, pid);
    }
    if (atoi(argv[2]) == P3) {
        printf("p: ESECUZIONE P3\n");
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

int openPIPE(char *path) {
    int fd;
    if ((fd = open(path, O_WRONLY)) == -1) {
        perror("P2: open pipe");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void initializationPIPE(char *path) {
    unlink(path);
    if (mknod(path, S_IFIFO, DEFAULT) == -1) {
        perror("P: mknod");
        exit(EXIT_FAILURE);
    }
    chmod(path, PERMISSION);
}