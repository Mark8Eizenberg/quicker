#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack *stack_t;

/**
 * @brief Create stack data structure
 * 
 * @param capacity capacity of stack
 * @param element_size size of each elements in stack
 * @return stack_t NULL if error, otherwise return stack
 */
stack_t stack_create(unsigned int capacity, unsigned int element_size);

/**
 * @brief Push element to stack
 * 
 * @param stack stack to push element
 * @param element pointer to element
 * @return int -1 if error, otherwise return 0
 */
int stack_push(stack_t stack, void *element);

/**
 * @brief Pop element from stack
 * 
 * @param stack stack to pop element
 * @return void* pointer to top element or NULL if stack empty
 */
void *stack_pop(stack_t stack);

/**
 * @brief Get count of elements in stack
 * 
 * @param stack stack to get count
 * @return int -1 if error, otherwise return count
 */
int stack_count(stack_t stack);

/**
 * @brief Destroy stack and free memory
 * 
 * @param stack stack to destroy
 */
void stack_destroy(stack_t *stack);

#endif //_STACK_H_