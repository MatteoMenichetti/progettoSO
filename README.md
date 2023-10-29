# progettoSO
Questo è il progetto relativo al corso di Sistemi Operativi.

L'obbiettivo è quello di costruire un semplice meccanismo di N-version programming.

Requisiti del progetto:

1) Input Manager: questo componente deve essere realizzato da almeno un processo e ha accesso al file dataset.csv. Input Manager effetua le seguenti azioni:
   - scarta la prima ria di dataset.csv;
   - con periodo di 1 secondo, legge un'intera riga di dataset.csv e la inivia al componente P1 tramite pipe, al componente P2 tramite socket ed al componente P3 tramite file condiviso.

2) P1: iterativamente, il componente P1, deve:
   - ricevere una stringa da Input Manager;
   - estrarre dalla stringa le porzioni di testo separate da virgole tramite strtok;
   - effettuare la somma intera dei caratteri estratti, prelevando i caratteri da sommare nell'ordine in sono prodotti dall'utilizzo di strtok;
   - inviare il risultato della somma al componente Decision Function;
  Inoltre, P1 deve includere la funzionalità random_failure che, se abilitata, modifica con probabilita 0.1 il risultato della somma, aggiungendo 10.

3) P2: iterativamente, il componente P2, deve:
   - ricevere una stringa da Input Manager;
   - estrarre dalla stringa le porzioni di testo separate da virgole senza utilizzare strtok;
   - effettuare la somma intera dei caratteri estratti, prelevando i caratteri da sommare a partire dall'ultimo della stringa, fino al primo;
   - inviare il risultato della somma al componente Decision Function;
  Inoltre, P2 deve includere la funzionalità random_failure che, se abilitata, modifica con probabilita 0.1 il risultato della somma, aggiungendo 20.

4) P3: iterativamente, il componente P3, deve:
   - ricevere una stringa da Input Manager;
   - estrarre dalla stringa le porzioni di testo separate da virgole senza utilizzare strtok;
   - effettuare la somma intera dei caratteri estratti, prelevando i caratteri da sommare a partire dal primo della stringa, fino all'ultimo;
   - inviare il risultato della somma al componente Decision Function;
  Inoltre, P3 deve includere la funzionalità random_failure che, se abilitata, modifica con probabilita 0.1 il risultato della somma, aggiungendo 30.

5) Decision Function: iterativamente, il componente Decision Function, deve:
   - ricevere un valore da P1, P2, P3;
   - scrivere i tre valori sul file "voted_output";
   - effettuare un voto di maggioranza sui tre valori ricevuti:
     i) se esiste una maggioranza scrive "SUCCESSO" sul file "system_log";
     ii) altrimenti scrive "SUCCESSO" sul file "system_log" ed invia un segnale SIGUSR1 a Failure Manager.
  Il componente invia, dopo ogni scrittura sul file "system_log", un messaggio I_AM_ALIVE al processo Watchdog.

6) Watchdog: il componente attende il messagio I_AM_ALIVE, con periodo 1 secondo da parte della Decision Function. Se non riceve questo messaggio per due periodi, invia un segnale SIGURSR1 al Failure Manager.

7) Failure Manager: il componente attende la ricezione di un segnale di tipo SIGUSR1 dal processo Decision Function ed alla ricezione di qeusto termina l'esecuzione di tutti i componenti.

## Compilazione
È prevista la compilazione su sistemi Unix-like tramite makefile. La sequenza è make all, make install. make clean per ripristinare all'origine.

## Avvio
Il programma è avviato con un singolo comando di shell, specificando se la modalità di esecuzione è
NORMALE o FALLIMENTO, e indicando il percorso del file dataset.csv. Nella modalità FALLIMENTO, la
funzonalità random_failure su P1, P2, e P3 è abilitata, mentre nella modalità NORMALE è disabilitata.

Esempio: ./main NORMALE /path/dataset.csv
