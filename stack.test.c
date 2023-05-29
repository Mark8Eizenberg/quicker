#include <stdio.h>

#include "tester/tester.h"
#include "quicker/stack.h"

int main(void) {
    
    unsigned const capacity = 10;

    stack_t stack = stack_create(capacity, sizeof(int));
    ASSERT_IS_NOT_NULL(stack, "%s", "Stack create successed");

    int numbers[] = {1,2,3,4,5,6,7,8,9,10};
    int *number = NULL;
    
    for(int i = 0; i < capacity; i++) {
        ASSERT_IS_EQUAL(stack_push(stack, &numbers[i]), 0, "Stack push successed number %d", numbers[i]);
    }

    ASSERT_IS_EQUAL(stack_push(stack, &numbers[0]), -1, "%s", "Stack push failed, because stack is full");

    for(int i = capacity - 1; i >= 0; i--) {
        number = stack_pop(stack);
        ASSERT_IS_NOT_NULL(number, "%s", "Stack pop successed");
        ASSERT_IS_EQUAL(*number, numbers[i], "Stack pop number %d, expected %d", *number,  numbers[i]);
    }

    ASSERT_IS_NULL(stack_pop(stack), "%s", "Stack pop failed, because stack is empty");
    ASSERT_IS_EQUAL(stack_push(stack, &numbers[0]), 0, "Stack push successed number %d", numbers[0]);
    number = stack_pop(stack);
    ASSERT_IS_NOT_NULL(number, "%s", "Stack pop successed");
    ASSERT_IS_EQUAL(*number, numbers[0], "Stack pop successed number %d", *number);

    stack_destroy(&stack);
    ASSERT_IS_NULL(stack, "%s", "Stack destroy successed");

    return 0;
}