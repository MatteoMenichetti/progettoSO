#include "../lib/p.h"

#define INT_ERR srand(time(NULL)) //neccaria invocazione per inizializzare la casualità nella generazione di numeri casuali

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("P: less than 3 arguments");
        exit(EXIT_FAILURE);
    }

    int flag = 0, pid = atoi(argv[3]);

    /* Con questo if si controlla la modalità d'esecuzione con cui i p devono essere eseguiti:
       Se l'argomento in argv[1] è uguale a FAILURE allora sarà attivata la modalità FALLIMENTO mettento flag uguale ad 1 */
    if ((strcmp(argv[1], FAILURE)) == 0) {
        INT_ERR;
        flag = 1;
    } else {
        //controllo necessario per stabilire se la modalità ricevuta è corretta
        if ((strcmp(argv[1], NORMAL)) != 0) {
            printf("P: MODALITY isn't correct\n");
            kill(0, SIGKILL);
        }
    }

    char cPnumber;
    strncpy(&cPnumber, argv[2], 1);
    int Pnumber = atoi((const char *) &cPnumber);

    /* Si avvia il p specificato dal Pnumber passato */

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


//metodo che compie la somma partendo dall'inizio della stringa
int sumFromFirst(char *token) {
    int s = 0;
    for (int l = 0; l < strlen(token); l++)
        s += *(token + l);
    return s;
}

//metodo che compie la somma partendo dalla fine della stringa
int sumFromLast(char *token) {
    int s = 0;
    for (int l = strlen(token); l >= 0; l--)
        s += *(token + l);
    return s;
}

//metodo che ci consente di scegliere quale tipo di somma eseguire
int sum(char *token, unsigned long start) {
    if (start == 0)return sumFromFirst(token);
    return sumFromLast(token);
}

//metodo che aggiunge il valore value alla somma con probabilità 0,1 se si verifica la condizione di fallimento
void errsum(int *somma, int value) {
    if ((random_failure == EVENT))*somma += value;
}