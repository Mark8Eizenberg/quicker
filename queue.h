#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef void* queue_t;

/**
 * @brief Creates a queue with the given element size and capacity
 * 
 * @param element_size size of the elements in the queue
 * @param capacity count of elements the queue can hold
 * @return queue_t NULL if queue could not be created, or queue_t otherwise
 */
queue_t queue_create(int element_size, int capacity);
void queue_destroy(queue_t queue);

/**
 * @brief Adds an element to the queue
 * 
 * @param queue queue to add element to
 * @param element element to add
 * @return int -1 if queue is error or queue full, 0 otherwise
 */
int queue_enqueue(queue_t queue, void* element);

/**
 * @brief Removes an element from the queue
 * 
 * @param queue queue to remove element from
 * @return void* pointer to the element removed
 */
void* queue_dequeue(queue_t queue);

#endif // _QUEUE_H_