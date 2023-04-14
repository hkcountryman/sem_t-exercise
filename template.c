/**
 * The main program for starting a threaded operation with a limited number of
 * threads.
 *
 * Suppose you wish to write multithreaded code that takes advantage of data
 * parallelism. You have determined a reasonable unit of work in the form of a
 * "chunk" of your larger dataset for a thread and you have discovered that you
 * see diminishing returns if you exceed 10 concurrent threads in your program
 * (see Amdahl's law).
 *
 * In the example below, the data are simply integers and the thread routine
 * that processes the data simply sleeps between 1 and 4 seconds based on the
 * number specified by the integer, but the details are inconsequential as this
 * could be applied to a more practical example of data parallelism.
 *
 * Given a queue containing all chunks of data, write code to process the data
 * in parallel and which uses a semaphore to limit the number of active threads.
 * Some starter code and optional pseudocode is provided.
 *
 * You may wish to consult the following man pages:
 *      semaphore.h(0P) - the POSIX Programmer's Manual entry for semaphore.h;
 *                    has more details on the POSIX implementation of semaphores
 *                    and the sem_t type.
 *      sem_init(3) - initialize an unnamed semaphore.
 *      sem_wait(3) - lock a semaphore.
 *      sem_post(3) - unlock a semaphore.
 *      pthread_attr_init(3) - initialize a thread attributes object.
 *      pthread_attr_setdetachstate(3) - set detach state attribute in a thread
 *                    attributes object.
 *
 * Man pages can be found online or installed on your system. The man pages are
 * located in the section indicated inside the parentheses. If a man page is
 * installed, you may access it by typing, e.g., `man 0p semaphore.h` (no
 * backticks) into your terminal to view semaphore.h(0P), or `man 3 sem_init`
 * to view sem_init(3).
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

    // TODO: When done, unlock the semaphore

    // TODO: End thread routine
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

    // TODO: Initialize the semaphore

    // TODO: Make thread attributes object to make detached (non-joinable) threads

    // TODO: Continue creating threads as long as the semaphore can be locked and
    // there is more data in the queue

    return 0;
}
