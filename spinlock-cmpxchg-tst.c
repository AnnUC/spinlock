#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "spinlock-cmpxchg.h"

int main()
{
    spinlock sl = SPINLOCK_INITIALIZER;
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
