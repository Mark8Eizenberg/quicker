#include "stack.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct _stack
{
    __uint8_t *data;
    unsigned int capacity;
    unsigned int element_size;
    unsigned int count;
    unsigned int top;
};

#define TO_STACK(s) ((struct _stack *)(s))

stack_t stack_create(unsigned int capacity, unsigned int element_size)
{
    struct _stack *s = (struct _stack *)malloc(sizeof(struct _stack));
    if (s == NULL)
        return NULL;

    s->data = (__uint8_t *)malloc(capacity * element_size);
    if (s->data == NULL)
        goto free_stack;

    s->capacity = capacity;
    s->element_size = element_size;
    s->count = 0;
    s->top = 0;
    return (stack_t)s;

free_stack:
    if (s->data != NULL)
        free(s->data);
    if (s != NULL)
        free(s);
    return NULL;
}

int stack_push(stack_t stack, void *element)
{
    struct _stack *s = TO_STACK(stack);
    if (s->count == s->capacity)
        return -1;
    memcpy(s->data + s->top, element, s->element_size);
    s->top += s->element_size;
    s->count++;
    return 0;
}

void *stack_pop(stack_t stack)
{
    struct _stack *s = TO_STACK(stack);
    if (s->count == 0)
        return NULL;
    s->top -= s->element_size;
    s->count--;
    return s->data + s->top;
}

int stack_count(stack_t stack)
{
    return TO_STACK(stack)->count;
}

void stack_destroy(stack_t *stack)
{
    if (stack == NULL)
        return;
    if (*stack == NULL)
        return;
    struct _stack *s = TO_STACK(*stack);
    if (s->data != NULL)
        free(s->data);
    if (s != NULL)
        free(s);
    *stack = NULL;
}
