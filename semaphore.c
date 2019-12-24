#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXN 5

char carattere = '\0';
sem_t semaforo;

void* consumer(void* arg) {
    sem_wait(&semaforo);
    printf("Consumer: leggo il valore %c\n", carattere);
    pthread_exit(NULL);
}

void* producer(void* arg) {
    printf("Procuder: genero un nuovo carattere\n");
    carattere = (char) (rand()%93) + 33;
    sem_post(&semaforo);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    srand(time(NULL));
    printf("Processo padre, creo threads\n");
    sem_init(&semaforo, 0, 0);

    for (int i = 0; i < MAXN; i++) {
        pthread_create(&t2, NULL, consumer, NULL);
        pthread_create(&t1, NULL, producer, NULL);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
    }

    return 0;
}

/*OUTPUT:
Processo padre, creo threads
Procuder: genero un nuovo carattere
Consumer: leggo il valore y
Procuder: genero un nuovo carattere
Consumer: leggo il valore N
Procuder: genero un nuovo carattere
Consumer: leggo il valore 3
Procuder: genero un nuovo carattere
Consumer: leggo il valore O
Procuder: genero un nuovo carattere
Consumer: leggo il valore B

 */
