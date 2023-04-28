#include <stdio.h>

#include "queue.h"

int main() {
    queue_t *queue = queue_create(sizeof(int), 10);

    for(int i = 0; i < 15; i++) {
        queue_enqueue(queue, &i);
    }

    for(int i = 0; i < 5; i++) {
        int *value = queue_dequeue(queue);
        if(value){
            printf("%d\n", *value);
        }
    }

    printf("---\n");

    for(int i = 0; i < 10; i++) {
        queue_enqueue(queue, &i);
    }

    for(int i = 0; i < 5; i++) {
        int *value = queue_dequeue(queue);
        if(value){
            printf("%d\n", *value);
        }
    }

    queue_destroy(queue);
}