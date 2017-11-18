#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

#include "spinlock-cmpxchg.h"

int main()
{
    spinlock sl = SPINLOCK_INITIALIZER;
    sl.lock = 0;
    sl.thread_id = 1;
    printf("%d\n",sl.lock);
    printf("%d\n",sl.thread_id);
    spin_lock(&sl,123);
    printf("%d\n",sl.lock);
    printf("%d\n",sl.thread_id);
    spin_unlock(&sl);
    printf("%d\n",sl.lock);
    printf("%d\n",sl.thread_id);
    return 0;
}
