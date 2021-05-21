#include "../lib/p.h"

char *split(char *buff) {
    char *token = strtok(buff, delim);
    do {
        printf("token = %s ", token);
        int s = sum(token, 0);
    } while ((token = strtok(NULL, delim)) != NULL);
    return NULL;
}
