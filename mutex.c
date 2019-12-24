
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 10

pthread_mutex_t M; /* def.mutex condiviso tra threads */
int DATA=0; /* variabile condivisa */
int accessi1=0; /*num. di accessi del thread 1 alla sez crit. */
int accessi2=0; /*num. di accessi del thread 2 alla sez crit. */


void *thread1_process (void * arg)
{ int k=1;
    while(k)
    {
        pthread_mutex_lock(&M); /*prologo */
        accessi1++;
        DATA++;
        k=(DATA>=MAX?0:1);  //se DATA>=MAX==true--> k=0 else k=1 --> expression ? if_true_then_process_it : or_process_it
        printf("accessi di T1: %d\n", accessi1);
        pthread_mutex_unlock(&M); /*epilogo */
    }
    pthread_exit (0);
}


void *thread2_process (void * arg)
{ int k=1;
    while(k)
    {
        pthread_mutex_lock(&M); /*prologo sez. critica */
        accessi2++;
        DATA++;
        k=(DATA>=MAX?0:1); //--> expression ? if_true_then_process_it : or_process_it
        printf("accessi di T2: %d\n", accessi2);
        pthread_mutex_unlock(&M); /*epilogo */
    }
    pthread_exit (0);
}


main()
{ pthread_t th1, th2;
    /* il mutex e` inizialmente libero: */
    pthread_mutex_init (&M, NULL);
    if (pthread_create(&th1, NULL, thread1_process, NULL) < 0)
    { fprintf (stderr, "create error for thread 1\n");
        exit (1);
    }
    if (pthread_create(&th2, NULL,thread2_process,NULL) < 0)
    { fprintf (stderr, "create error for thread 2\n");
        exit (1);
    }
    pthread_join (th1, NULL);
    pthread_join (th2, NULL);
}
/*
Test
        $
$ gcc -D_REENTRANT -o tlock lock.c -lpthread
        $ ./tlock
        accessi di T2: 1
accessi di T1: 1
accessi di T2: 2
accessi di T1: 2
accessi di T1: 3
accessi di T1: 4
accessi di T1: 5
accessi di T1: 6
accessi di T1: 7
accessi di T1: 8
accessi di T2: 3

il due thread si stanno passando il lock ogni giro del while ma non sappiamo chi acquisira successivamente il lock
quello è deciso a caso dall OS, cio che sappiamo è che in totale il lock sara passato MAX volte--> ci saranno MAX accessi
$//
// Created by Luca on 11/11/2019.
//
*/
