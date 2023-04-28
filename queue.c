#include "queue.h"

#include <stdlib.h>
#include <string.h>

#define TO_QUEUE(Q) ((struct _private_queue_struct *)(Q))

struct _private_queue_struct
{
    void *elements;
    int element_size;
    int capacity;
    int head;
    int tail;
};

queue_t queue_create(int element_size, int capacity)
{
    struct _private_queue_struct *queue = 
        (struct _private_queue_struct *)malloc(sizeof(struct _private_queue_struct));
    
    if(queue == NULL){
        return NULL;
    }

    queue->elements = malloc(element_size * capacity);
    if(queue->elements == NULL){
        free(queue);
        return NULL;
    }

    queue->element_size = element_size;
    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = 0;
    return queue;
}

void queue_destroy(queue_t queue)
{
    if(queue != NULL){
        struct _private_queue_struct *q = TO_QUEUE(queue);
        free(q->elements);
        free(q);
    }
}

int queue_enqueue(queue_t queue, void *element)
{
    if(queue == NULL){
        return -1;
    }

    struct _private_queue_struct *q = TO_QUEUE(queue);
    
    int new_tail = (q->tail + 1) % q->capacity;
    if(new_tail == q->head){
        return -1;
    }

    memcpy(q->elements + q->tail * q->element_size, element, q->element_size);
    q->tail = new_tail;
    return 0;
}

void *queue_dequeue(queue_t queue)
{
    if(queue == NULL){
        return NULL;
    }

    struct _private_queue_struct *q = TO_QUEUE(queue);
    
    if(q->head == q->tail){
        return NULL;
    }

    void *element = q->elements + q->head * q->element_size;
    q->head = (q->head + 1) % q->capacity;
    return element;
}
