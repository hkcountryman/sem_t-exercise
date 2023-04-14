/**
 * Definitions for a queue data structure and associated operations.
 *
 * The exact implementation details are unimportant but provided for context.
 * Memory management for the queue's list structure is taken care of in this
 * module, but the contents of a queue entry (i.e., struct node.datum) must be
 * managed separately. There is no provided destructor function because it is
 * not needed for this problem.
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

#include <stdlib.h>

#include "queue.h"

/**
 * Initialize a queue.
 * @return a pointer to the new queue
 */
struct queue *queue_init(void)
{
    struct queue *q = malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/**
 * Add a node to the end of the queue.
 * @param q a pointer to the queue to add to
 * @param datum a pointer to the node's data
 */
void queue_add(struct queue *q, void *datum)
{
    struct node *n = malloc(sizeof(struct node));
    n->datum = datum; // datum should already be allocated in heap
    n->next = NULL;
    if (q->head == NULL)
    {
        q->head = n;
        q->tail = n;
    }
    else
    {
        q->tail->next = n; // connect to end of list
        q->tail = n;       // move tail pointer to the newer node
    }
}

/**
 * Retrieve a node from the beginning of the queue.
 * @param q a pointer to the queue to retrieve from
 * @return the data at the head of the queue, or NULL if the queue is empty.
 */
void *queue_get(struct queue *q)
{
    if (q->head == NULL)
    {
        return NULL;
    }
    else
    {
        void *datum = q->head->datum; // take from earliest added node
        struct node *n = q->head;     // save reference to current head
        q->head = q->head->next;      // move head to point to its next node
        free(n);                      // free former head node, but don't free datum
        return datum;
    }
}

/**
 * Test whether a queue is empty.
 * @param q a pointer to the queue to test
 * @return 1 if it is empty; otherwise 0
 */
unsigned queue_isempty(struct queue *q)
{
    return q->head == NULL ? 1 : 0;
}
