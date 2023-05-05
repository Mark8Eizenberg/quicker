#include "queue.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TO_QUEUE(Q) ((struct _private_queue_struct *)(Q))

struct _private_queue_struct
{
    __uint8_t *elements;
    int element_size;
    int capacity;
    int head;
    int tail;
    unsigned count;
};

queue_t queue_create(int element_size, int capacity)
{
    
    struct _private_queue_struct *queue = 
        (struct _private_queue_struct *)malloc(sizeof(struct _private_queue_struct));
    
    if(queue == NULL){
        return NULL;
    }

    queue->elements = (__uint8_t *)malloc(capacity * element_size);
    if(queue->elements == NULL){
        free(queue);
        return NULL;
    }

    queue->element_size = element_size;
    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = -1;
    queue->count = 0;
    return queue;
}

void queue_destroy(queue_t *queue)
{
    if(*queue != NULL){
        struct _private_queue_struct *q = TO_QUEUE(*queue);
        free(q->elements);
        free(q);
        *queue = NULL;
    }
}

int queue_enqueue(queue_t queue, void *element)
{
    if(queue == NULL){
        return -1;
    }

    struct _private_queue_struct *q = TO_QUEUE(queue);
        
    if(q->count == q->capacity){
        return -1;
    }
    q->tail = (q->tail + 1) % q->capacity;

    memcpy(q->elements + q->tail * q->element_size, (__uint8_t*)element, q->element_size);
    q->count++;
    return 0;
}

void *queue_dequeue(queue_t queue)
{
    if(queue == NULL){
        return NULL;
    }

    struct _private_queue_struct *q = TO_QUEUE(queue);
    
    if(q->count == 0){
        return NULL;
    }
    q->count--;

    void *element = q->elements + q->head * q->element_size;
    q->head = (q->head + 1) % q->capacity;
    return element;
}
