//
// Created by zano on 24/12/19.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int conto=200;
pthread_mutex_t mux =PTHREAD_MUTEX_INITIALIZER;
sem_t sem;


void* thr_fun1(void* arg)
{
    int deposito=300;
    pthread_mutex_lock(&mux);
    printf("il nuovo valore del conto è %d + deposito %d = %d  \n ",conto,deposito,conto+deposito);
    conto=conto+deposito;
    sem_post(&sem);
    pthread_mutex_unlock(&mux);
}

void* thr_fun2(void* arg)
{
    int prelievo= 100;

    if(prelievo>conto){
        sem_wait(&sem);
        pthread_mutex_lock(&mux);
        printf("il nuovo valore del conto è %d - prelievo %d = %d  \n ",conto,prelievo,conto-prelievo);
        conto=conto-prelievo;
        pthread_mutex_unlock(&mux);
    }
    else
    {
        pthread_mutex_lock(&mux);
        printf("il nuovo valore del conto è %d - prelievo %d = %d  \n ",conto,prelievo,conto-prelievo);
        conto=conto-prelievo;
        pthread_mutex_unlock(&mux);
    }
}

int main(int argc ,char* argv[])
{
    sem_init(&sem,0,0);
    pthread_t th1,th2;
    pthread_create(&th2,NULL,thr_fun2,NULL);
    pthread_create(&th1,NULL,thr_fun1,NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    sem_destroy(&sem);
    return 0;
}

/*
 * il semaforo mi permette di eseguire sempre prima il deposito rispetto al prelievo se il valore del conto è insuff
 */