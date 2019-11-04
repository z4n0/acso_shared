#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
//non funzia
#define NITER 1000000

int cnt = 0;
sem_t semname;
//unsigned int n=1;


void * Count(void * a)
{
    sem_wait(&semname);
    int i, tmp;
    for(i = 0; i < NITER; i++)
    {
        tmp = cnt;      /* copy the global cnt locally */
        tmp = tmp+1;    /* increment the local copy */
        cnt = tmp;      /* store the local value into the global cnt */ 
    }
    sem_post(&semname);
}


int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;
    sem_init(&semname,0,1);

    if(pthread_create(&tid1, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }
    sleep(1);

    if(pthread_create(&tid2, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if (cnt < 2 * NITER) 
        printf("\n BOOM! cnt is [%d], should be %d\n", cnt, 2*NITER);
    else
        printf("\n OK! cnt is [%d]\n", cnt);
    sem_destroy(&semname);
    pthread_exit(NULL);
}
