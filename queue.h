/**
 * Declarations for a queue data structure and associated operations.
 *
 * Structs:
 *      struct node - contains a pointer to some data to store in this list
 *                    entry and a pointer to the next node in the list.
 *      struct queue - contains pointers to the head and tail of a linked list.
 *
 * Functions:
 *      queue_init(void) - allocate the queue on the heap and initialize its
 *                         head and tail pointers to NULL.
 *      queue_add(struct queue *q, void *datum) - allocate a new entry in the
 *                         queue, which will contain the datum pointer and will
 *                         become the new tail of the queue.
 *      queue_get(struct queue *q) - retrieve the datum pointer located at the
 *                         head of the queue, remove (deallocate) the current
 *                         head, and set the queue's head to point to the next
 *                         item in the queue.
 *      queue_isempty(struct queue *q) - check whether the queue is empty.
 *
 * @author H Countryman
 * @version 1
 */

#ifndef QUEUE_H
#define QUEUE_H

/** An entry in the queue. */
struct node
{
    void *datum;       // can be anything
    struct node *next; // next node in list
};

/** The queue, a series of connected nodes from head to tail. */
struct queue
{
    struct node *head; // head will be the earliest added node
    struct node *tail; // tail will be the most recently added node
};

/**
 * Initialize a queue.
 * @return a pointer to the new queue
 */
struct queue *queue_init(void);

/**
 * Add a node to the end of the queue.
 * @param q a pointer to the queue to add to
 * @param datum a pointer to the node's data
 */
void queue_add(struct queue *q, void *datum);

/**
 * Retrieve a node from the beginning of the queue.
 * @param q a pointer to the queue to retrieve from
 * @return the data at the head of the queue, or NULL if the queue is empty.
 */
void *queue_get(struct queue *q);

/**
 * Test whether a queue is empty.
 * @param q a pointer to the queue to test
 * @return 1 if it is empty; otherwise 0
 */
unsigned queue_isempty(struct queue *q);

#endif
