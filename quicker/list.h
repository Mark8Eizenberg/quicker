#ifndef _LIST_H_
#define _LIST_H_

typedef void* list_t;
typedef void* iterator_t;

/**
 * @brief Create a list
 * 
 * @param element_size size of the elements in list
 * @param capacity capacity of the list
 * @return list_t return NULL if error otherwise a list_t
 */
list_t list_create(int element_size, int capacity);

/**
 * @brief Destroy passed list
 * 
 * @param list pointer to the list_t to destroy
 */
void list_destroy(list_t *list);

/**
 * @brief Get size of passed list
 */
int list_get_size(list_t list);

/**
 * @brief Get capacity (max count for elements) of passed list
 */
int list_capacity(list_t list);

/**
 * @brief Get iterator to the first element
 * 
 * @return iterator_t return NULL if empty otherwise a iterator_t
 */
iterator_t list_begin(list_t list);

/**
 * @brief Get iterator to the last element
 * 
 * @return iterator_t return NULL if empty otherwise a iterator_t
 */
iterator_t list_end(list_t list);

/**
 * @brief Get next iterator of passed iterator
 * 
 * @return iterator_t NULL if iterator is at the end otherwise a iterator_t
 */
iterator_t list_get_next(iterator_t iterator);

/**
 * @brief Get previous iterator of passed iterator
 * 
 * @return iterator_t NULL if iterator is at the beginning otherwise a iterator_t
 */
iterator_t list_get_previous(iterator_t iterator);

/**
 * @brief Get pointer to the element of passed iterator
 * 
 * @return void* element pointer
 */
void* list_get_element(iterator_t iterator);

/**
 * @brief Add element to the list
 * 
 * @param list list_t to add element to
 * @param element pointer to the element to add
 * @return int -1 if error otherwise 0
 */
int list_add_element(list_t list, void* element);

void list_remove_element(list_t list, iterator_t *iterator);

#endif // _LIST_H_