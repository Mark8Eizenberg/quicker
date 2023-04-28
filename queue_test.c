#include <stdio.h>

#include "tester.h"
#include "queue.h"

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
}