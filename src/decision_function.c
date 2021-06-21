#include "../lib/ipc.h"

#define LOGPATH "../logs/system_log"
#define VOTEDPATH "../logs/voted_output"

#define WATCHDOG 0
#define FAILURE_MANAGER 1
#define VOTEDPOS 3
#define LOGPOS 4

#define FALLIMENTO "FALLIMENTO\n"
#define SUCCESSO "SUCCESSO\n"


/*metodo che scrive sul file Voted Output i risultati delle somme e scrive SUCCESSO o FALLIMENTO
  sul file System_Log */
void writeOnLog(int fd[], int value_Split_Sum[], char buffer[]) {
    dprintf(fd[VOTEDPOS], "p1 = %d p2 = %d p3 = %d \n", value_Split_Sum[P1],
            value_Split_Sum[P2],
            value_Split_Sum[P3]);

    if ((write(fd[LOGPOS], buffer, strlen(buffer))) == -1) {
        perror("DF: write on voted_output");
        exit(EXIT_FAILURE);
    }
}


//metodo che stabilisce se c'è stato un voto di maggioranza oppure no
int EqualityCondition(int vp1, int vp2, int vp3) {
    if (vp1 != vp2 && vp1 != vp3 && vp2 != vp3)return 0;
    return 1;
}

//metodo che richiama EqualityCondition e writeOnLog e invia i segnali a WatchDog e a Failure Manager
void controllValueRecived(int *fd, int *pid, int *value_Split_Sum) {
    char *buffer; //buffer in cui viene inserito l'esito della votazione
    if (!EqualityCondition(value_Split_Sum[P1], value_Split_Sum[P2], value_Split_Sum[P3]))
        buffer = FALLIMENTO;
    else buffer = SUCCESSO;

    writeOnLog(fd, value_Split_Sum, buffer);

    if ((kill(pid[WATCHDOG], SIGUSR1)) == -1) {
        perror("decision_function: kill on watchdog");
        exit(EXIT_FAILURE);
    }

    if ((strcmp(buffer, FALLIMENTO)) == 0) {
        printf("decision_function: send SIGUSR1 to failure_manager (FALLIMENTO)\n");
        kill(pid[FAILURE_MANAGER], SIGUSR1);
    }
}

//metodo che crea e apre in scrittura i file System Log e Voted Output
void openFILE(int *fd) {
    if (((fd[LOGPOS] = open(LOGPATH, O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONFILE)) == -1)) {
        perror("DF: open log");
        exit(EXIT_FAILURE);
    }

    if ((fd[VOTEDPOS] = open(VOTEDPATH, O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONFILE)) == -1) {
        perror("decision_function: open voted_output");
        exit(EXIT_FAILURE);
    }
}

// metodo che apre in lettura le pipe PIPEDP1PATH, PIPEDP2PATH e PIPEDP3PATH
void openPIPES(int fd[]) {
    char *paths[3] = {PIPEDP1PATH, PIPEDP2PATH, PIPEDP3PATH};
    int flags[3] = {O_RDONLY, O_RDONLY, O_RDONLY};

    for (int i = 0; i < 3; i++)
        fd[i] = openPIPE(paths[i], flags[i]);

}

int main(void) {
    printf("decision_function: start\n");

    //signal(SIGUSR1, SIG_IGN);

    /* fd[] array che contiene i file descriptor di PIPEDP1PATH, PIPEDP2PATH e PIPEDP3PATH e dei file System Log e Voted Output
       pid[] array che contiene i pid dei processi Failure Manager e WatchDog
       value_Split_Sum array in cui inseriamo le somme inviate dai tre processi p
    */
    int fd[5], pid[2], value_Split_Sum[3];

    //creazione processo failure manager
    if (!(pid[FAILURE_MANAGER] = fork()))
        execl("./failure_manager", "failure_manager", (char *) NULL);

    //creazione processo WatchDog
    if (!(pid[WATCHDOG] = fork())) {
        char *failure_manager_pid = (char *) calloc(1, sizeof(pid[FAILURE_MANAGER]));
        sprintf(failure_manager_pid, "%d", pid[FAILURE_MANAGER]); // Si invia il pid di failure_manager cosi che gli possa inviare un segnale SIGUSR1
        execl("./watchdog", "watchdog", failure_manager_pid, (char *) NULL);
    }

    openFILE(fd);
    openPIPES(fd);

    // si ricevono le somme dai tre processi p
    while (0 == 0) {
        if ((read(fd[P1], &value_Split_Sum[P1], sizeof(int))) == -1) {
            perror("decision_function: read P1");
            exit(EXIT_FAILURE);
        }

        if ((read(fd[P2], &value_Split_Sum[P2], sizeof(int))) == -1) {
            perror("decision_function: read P2");
            exit(EXIT_FAILURE);
        }

        if ((read(fd[P3], &value_Split_Sum[P3], sizeof(int))) == -1) {
            perror("decision_function: read P3");
            exit(EXIT_FAILURE);
        }
        controllValueRecived(fd, pid, value_Split_Sum);

    }
}

