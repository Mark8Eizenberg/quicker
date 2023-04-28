#include <stdio.h>

#include "tester/tester.h"
#include "quicker/queue.h"

typedef struct{
    int a;
    int b;
} a_t;

void print_a(a_t *a)
{
    printf("%d %d\n", a->a, a->b);
}

int main()
{
    const int size = 5;
    queue_t queue = queue_create(sizeof(int), size);

    ASSERT_IS_NOT_NULL(queue, "%s", "Create queue");

    int i, res;
    for (i = 0; i < 10; ++i)
    {
        res = queue_enqueue(queue, &i);
        if (i < size)
        {
            ASSERT_IS_EQUAL(0, res, "Enqueue to queue element %d", i);
        }
        else
        {
            ASSERT_IS_EQUAL(-1, res, "Can not enqueue to queue element %d, queue full", i);
        }
    }

    int *in_queue = NULL;
    for (i = 0; i < size; ++i)
    {
        in_queue = (int *)queue_dequeue(queue);
        ASSERT_IS_NOT_NULL(in_queue, "Dequeue from queue element %d", i);
        ASSERT_IS_EQUAL(i, *in_queue, "Dequeued element %d == %d", i, *in_queue);
    }

    in_queue = queue_dequeue(queue);
    ASSERT_IS_NULL(in_queue, "%s", "Dequeue from empty queue");

    for (i = 0; i < 10; ++i)
    {
        res = queue_enqueue(queue, &i);
        if (i < size)
        {
            ASSERT_IS_EQUAL(0, res, "Enqueue to queue element %d", i);
        }
        else
        {
            ASSERT_IS_EQUAL(-1, res, "Can not enqueue to queue element %d, queue full", i);
        }
    }

    for (i = 0; i < size; ++i)
    {
        in_queue = (int *)queue_dequeue(queue);
        ASSERT_IS_NOT_NULL(in_queue, "Dequeue from queue element %d", i);
        ASSERT_IS_EQUAL(i, *in_queue, "Dequeued element %d == %d", i, *in_queue);
    }
    in_queue = queue_dequeue(queue);
    ASSERT_IS_NULL(in_queue, "%s", "Dequeue from empty queue");

    queue_destroy(&queue);
    ASSERT_IS_TRUE(queue_enqueue(queue, &i) == -1, "%s", "Can not enqueue to destroyed queue");
    ASSERT_IS_NULL(queue_dequeue(queue), "%s", "Can not dequeue from destroyed queue");

    queue_t queue_a = queue_create(sizeof(a_t), size);

    a_t a = {1,2};
    a_t b = {3,4};

    queue_enqueue(queue_a, &a);
    queue_enqueue(queue_a, &b);

    a_t *r = (a_t *)queue_dequeue(queue_a);

    ASSERT_IS_NOT_NULL(r, "%s", "Dequeue from queue_a");
    ASSERT_IS_EQUAL(1, r->a, "Dequeued element a->a == %d", r->a);
    ASSERT_IS_EQUAL(2, r->b, "Dequeued element a->b == %d", r->b);
    
    r = (a_t *)queue_dequeue(queue_a);
    ASSERT_IS_NOT_NULL(r, "%s", "Dequeue from queue_a");
    ASSERT_IS_EQUAL(3, r->a, "Dequeued element b->a == %d", r->a);
    ASSERT_IS_EQUAL(4, r->b, "Dequeued element b->b == %d", r->b);

    r = (a_t *)queue_dequeue(queue_a);
    ASSERT_IS_NULL(r, "%s", "Dequeue from empty queue_a");
    queue_destroy(&queue_a);
    ASSERT_IS_EQUAL(-1, queue_enqueue(queue_a, &a), "%s", "Can not enqueue to destroyed queue_a");
    ASSERT_IS_NULL(queue_dequeue(queue_a), "%s", "Can not dequeue from destroyed queue_a");
    ASSERT_IS_NULL(queue_a, "%s" ,"queue_a is NULL");

    return 0;

}