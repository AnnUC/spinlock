#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>

#include "spinlock-cmpxchg.h"

#define NCOUNTER 1000000
static long counter=0;
spinlock sl;

void *inc_thread(void *id) {
    /* Start lock unlock test. */
    for (int j = 0; j < NCOUNTER; j++) {
        spin_lock(&sl);
        counter++;
        spin_unlock(&sl);
    }
}

int main()
{

    pthread_t *thr;
    long nthr = 10;
    thr = calloc(sizeof(*thr), nthr);
    for (long i = 0; i < nthr; i++) {
        if (pthread_create(&thr[i], NULL, inc_thread, (void *)i) != 0) {
            perror("thread creating failed");
        }
    }

    for (long i = 0; i < nthr; i++)
        pthread_join(thr[i], NULL);
    printf("total count: %ld\n",counter);
    return 0;

}
