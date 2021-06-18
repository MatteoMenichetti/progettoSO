#include "../lib/common.h"

int allarme = 0; // variabile che indica se è avvenuto un allarme

/*funzione handler che gestisce il segnale SIGALRM: quando riceve un SIGALRM imposta la
  variabile allarme a 1 (notifica che è avvenuto un allarme) */
void SIGALRM_handler() {
    allarme = 1;
}

/*funzione handler che gestisce il segnale SIGUSR1: quando watchDog riceve un segnale SIGUSR1
  stampa il messaggio "I_AM_ALIVE" e riattiva l'allarme */
void SIGUSR1_handler() {
    printf("watchdog: I_AM_ALIVE\n");
    alarm(2);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("watchdog: less than 2 arguments");
        exit(EXIT_FAILURE);
    }

    printf("watchdog: start\n");

    int pid_failure_manager = atoi(argv[1]);
    
    //si ridefinisce la funzione handler per i segnali SIGUSR1 e SIGALRM
    signal(SIGUSR1, SIGUSR1_handler);
    signal(SIGALRM, SIGALRM_handler);

   //si imposta un timer iniziale
    alarm(2);
    
    /*questo ciclo mette in pausa watchdog fino alla ricezione di un allarme */
    while (allarme == 0) pause();
    
    //invio segnale al failure manager 
    kill(pid_failure_manager, SIGUSR1);
}