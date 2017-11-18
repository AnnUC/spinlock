#ifndef _SPINLOCK_CMPXCHG_H
#define _SPINLOCK_CMPXCHG_H
#endif

typedef struct {
    volatile unsigned int lock;
    volatile pid_t thread_id;
} spinlock;

#define SPINLOCK_ATTR static __inline __attribute__((always_inline, no_instrument_function))

/* Pause instruction to prevent excess processor bus usage */
#define cpu_relax() asm volatile("pause\n": : :"memory")

SPINLOCK_ATTR char __testandset(spinlock *p, long old_val, long new_val)
{
    char result = 0;
    asm volatile (
            "lock; cmpxchgq %4, %1"
            : "=q" (result), "=m" (*p)
            : "m" (*p), "a" (old_val), "r" (new_val)
            : "memory");
    return result;
}

SPINLOCK_ATTR void spin_lock(spinlock *lock, pid_t tid)
{
    long l_tid = tid;
    l_tid = (l_tid << 32) + 1;
    while (__testandset(lock, 0, l_tid)) {
        cpu_relax();
    }
}

SPINLOCK_ATTR void spin_unlock(spinlock *s)
{
    long new_val = 0;
    asm volatile ("xchgq %0,%1"
                :
                :"m" (*s), "r" (new_val)
                :"memory");
}

#define SPINLOCK_INITIALIZER { 0 }

