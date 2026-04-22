# Implementation Logic from First Principles

## Naive Implementation

- Say, 3 is the barrier count. That means two threads will get blocked before the third one comes and unblocks the other threads.
- What this means is, if count of threads arrived are lesser than 3, call pthread_cond_wait function; when it becomes 3, call the pthread_cond_broadcast function.
- We will have to check whether count of threads has become 3 in a while loop in order to avoid spurious wake-ups. The thread can wake up without any signal.

With this logic in place, we end up with following implementation.

```c++
void xthread_barrier_wait(xthread_barrier_t* barrier) {
    pthread_mutex_lock(&barrier->mutex);

    barrier->counter++;

    if (barrier->counter == barrier->barrier_count) {
        barrier->counter = 0;
        pthread_cond_broadcast(&barrier->cv);
    } else {
        while (barrier->counter != 0) {
            pthread_cond_wait(&barrier->cv, &barrier->mutex);
        }
    }

    pthread_mutex_unlock(&barrier->mutex);
}
```

From the surface, this looks complete. But, it is incomplete and hides a bug.

This implementation can cause Deadlocks that can emerge when exposed to resource contention or due to slow and fast threads.

## How a Deadlock can emerge?

### Scenario

- Thread barrier count is 3 threads
- Threads T1 and T2 are fast, while T3 is slower
- The same thread barrier is being consumed in a loop. For examples

```c++
void* worker_fn(void* arg) {
    int i = 1;
    
    while (1) {
        printf("Thread waiting at barrier in cycle %d\n", i);
        xthread_barrier_wait(&barrier);
        printf("Thread passed barrier in cycle %d\n", i);
        
        i++;
    }

    return NULL;
```

### Timeline of events leading to Deadlock

1. At t = 0, Threads T1 and T3 arrive at the barrier, gets blocked, and sets the counter to 2
2. At t = 1, Thread T2 arrives at the barrier, does the following, and exits
   - Counter is set to 0
   - Signal is sent to the blocked threads T1 and T3
3. At t = 2, Before the thread T2 could enter the next cycle of the loop, it gets preempted by OS
4. At t = 3, Thread T1 wakes-up from the blocked state and finds the while loop condition `counter != 0` as false and exits the `while` loop. It moves to the next cycle and reaches thread barrier again.
   - Sets the counter to 1
   - T1 Gets blocked
5. At t = 4, Thread T2 gets scheduled again reaches the barrier, increments the counter to 2, and gets blocked.
6. At t = 5, Thread T3 finally wakes up and checks whether the counter is != 0. It finds the condition as true and again goes back to sleep.
7. Now, Thread T1 and T2 are blocked at barrier as the counter is 2. Thread 3 is waiting as well for a signal. This is the deadlock situation.

## Fix: Track Generations

Fixed version
```c++
typedef struct {
    int barrier_count;
    int counter;
    int generation; // Addition
    pthread_mutex_t mutex;
    pthread_cond_t cv;
} xthread_barrier_t;

void xthread_barrier_wait(xthread_barrier_t* barrier) {
    pthread_mutex_lock(&barrier->mutex);

    barrier->counter++;

    if (barrier->counter == barrier->barrier_count) {
        barrier->counter = 0;
        barrier->generation++;
        pthread_cond_broadcast(&barrier->cv);
    } else {
        const int last_generation = barrier->generation; // Notes down the last generation
        while (last_generation == barrier->generation) { // Changed the condition
            pthread_cond_wait(&barrier->cv, &barrier->mutex);
        }
    }

    pthread_mutex_unlock(&barrier->mutex);
}
```

1. The root cause is that wait predicate in while loop is not specific enough to the event it is waiting for.
2. `counter != 0` doesn't mean "my cycle is incomplete" — it just happens to coincide with that meaning under ideal conditions. When fast threads corrupt the counter from the next cycle, the predicate loses that coincidence entirely and becomes meaningless.
3. The solution to this is tracking generation of barrier cycle and breaking the while loop condition when generation changes.
4. Counter is used for deciding when to wait and when to broadcast. Generation is used by sleeping threads to decide whether to exit the while loop after being woken up.
5. Notice how generation changes only when the counter is same as thread barrier count. Counter is affected by fast/slow threads whereas Generation is unaffected by it.