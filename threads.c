#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} t_arg;

typedef struct {
    int sum;
    int diff;
} t_res;


void* thread_func ( void* pair ) {
    t_res *r = (t_res*) malloc( sizeof( t_res ) );
    t_arg *x = (t_arg*) pair;
    r->sum = x->a + x->b;
    r->diff = x->a - x->b;
    pthread_exit( r );
}


int main () {
    t_arg x;
    t_res *y;
    pthread_t tid;
    void* arg;
    void* ret;

    x.a = 1;
    x.b = 2;
    
    arg = (void*)(&x);
    
    pthread_create ( &tid, NULL, thread_func, arg );
 
    pthread_join( tid, &ret );

    y = (t_res*) ret;
    
    printf("%d + %d = %d\n", x.a, x.b, y->sum);
    printf("%d - %d = %d\n", x.a, x.b, y->diff);

    // CASO 1
    free( ret );

    return 0;
}
