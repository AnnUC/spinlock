#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

#include "spinlock-cmpxchg.h"

int main()
{
    spinlock sl;
    sl.lock = 0;
    sl.thread_id = 0;
    printf("%d\n",sl.lock);
    printf("%d\n",sl.thread_id);
    spin_lock(&sl);
    printf("%d\n",sl.lock);
    printf("%d\n",sl.thread_id);
    spin_unlock(&sl);
    printf("%d\n",sl.lock);
    printf("%d\n",sl.thread_id);
    return 0;
}
