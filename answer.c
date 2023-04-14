/**
 * The main program for starting a threaded operation with a limited number of
 * threads.
 *
 * This is one possible solution you could implement in template.c.
 *
 * @author H Countryman
 * @version 1
 */

// needed for nanosleep() from time.h
#define _POSIX_C_SOURCE 199506L

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "queue.h"

/** Arbitrary number of threads we have somehow determined to be optimal. */
#define MAX_THREADS 10

/** Global semaphore. */
static sem_t sem;

/**
 * Do something with the data.
 * @param args an int pointer
 * @return NULL
 */
static void *thread_job(void *args)
{
    // Operate on the data
    int *i = (int *)args;                         // cast to the expected type
    int s = 1 + *i % 4;                           // between 1 and 4
    nanosleep((struct timespec[]){{s, 0}}, NULL); // suspend execution 1-4 s

    // When done, unlock the semaphore
    sem_post(&sem);

    // End thread routine
    // Note: we don't care about returning anything to the calling thread, so
    // using pthread_exit() is unnecessary
    return NULL;
}

/**
 * The main function: get some kind of split data from somewhere and operates on
 * up to MAX_THREADS chunks of data at a time using detached threads.
 * @return 0
 */
int main(void)
{
    // Get queue of data from somewhere
    struct queue *q = queue_init();
    for (int i = 0; i < 25; i++)
    {
        int *d = malloc(sizeof(int));
        *d = i; // example data in the form of an int; could be anything
        queue_add(q, d);
    }

    // Initialize the semaphore
    sem_init(&sem, 0, MAX_THREADS);

    // Make thread attributes object to make detached (non-joinable) threads
    pthread_attr_t attr;                                         // use to make detached (non-joinable) threads
    pthread_attr_init(&attr);                                    // initialize to default attributes
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); // detach

    // Continue creating threads as long as the semaphore can be locked and
    // there is more data in the queue
    do
    {
        pthread_t tid; // buffer to store thread ID
        int *q_next = queue_get(q);
        if (q_next)
        {
            pthread_create(&tid, &attr, &thread_job, q_next);
        }
    } while (sem_wait(&sem) == 0 && !queue_isempty(q));

    return 0;
}
