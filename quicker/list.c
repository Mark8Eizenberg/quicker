/*****************************************************************************
 * Algorithm for creating a list with a queue, where will be stored the free nodes.
 * Using queue is speed up the process of adding and removing elements.
 *******************************************************************************/

#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "queue.h"

#define TO_LIST(L) ((struct _private_list *)(L))
#define TO_NODE(N) ((struct _private_list_node *)(N))

struct _private_list_node
{
    __uint8_t *element;
    struct _private_list_node *next;
    struct _private_list_node *prev;
};

struct _private_list
{
    __uint8_t *elements_memo;
    struct _private_list_node *nodes;
    struct _private_list_node *head;
    struct _private_list_node *tail;
    queue_t free_nodes;
    size_t size;
    size_t capacity;
    size_t element_size;
};

list_t list_create(int element_size, int capacity)
{
    struct _private_list *list = malloc(sizeof(struct _private_list));
    if (list == NULL)
        goto error_exit;

    list->free_nodes = queue_create(sizeof(unsigned), capacity);
    if (list->free_nodes == NULL)
        goto free_list;

    list->nodes = malloc(sizeof(struct _private_list_node) * capacity);
    if(list->nodes == NULL)
        goto free_queue;

    list->elements_memo = (__uint8_t *)malloc(element_size * capacity);
    if (list->elements_memo == NULL)
        goto free_nodes;

    for (int i = 0; i < capacity; i++)
    {
        list->nodes[i].next = NULL;
        list->nodes[i].prev = NULL;
        list->nodes[i].element = &(list->elements_memo[i * element_size]);

        if (queue_enqueue(list->free_nodes, &i) != 0)
        {
            goto free_queue;
        }
    }

    list->head = NULL;
    list->tail = NULL;
    list->capacity = capacity;
    list->element_size = element_size;
    list->size = 0;

    return list;
free_nodes:
    free(list->nodes);
free_queue:
    queue_destroy(list->free_nodes);
free_list:
    free(list);
error_exit:
    return NULL;
}

void list_destroy(list_t *list)
{
    if (list == NULL)
        return;

    struct _private_list *l = TO_LIST(*list);
    queue_destroy(&l->free_nodes);
    free(l->nodes);
    free(l->elements_memo);
    free(l);
    *list = NULL;
}

int list_get_size(list_t list)
{
    if (list == NULL)
        return -1;
    struct _private_list *l = TO_LIST(list);
    return l->size;
}

int list_capacity(list_t list)
{
    if (list == NULL)
        return -1;
    struct _private_list *l = TO_LIST(list);
    return l->capacity;
}

iterator_t list_begin(list_t list)
{
    if (list == NULL)
        return NULL;
    struct _private_list *l = TO_LIST(list);
    return l->head;
}

iterator_t list_end(list_t list)
{
    if (list == NULL)
        return NULL;
    struct _private_list *l = TO_LIST(list);
    return l->tail;
}

iterator_t list_get_next(iterator_t iterator)
{
    if (iterator == NULL)
        return NULL;
    struct _private_list_node *node = TO_NODE(iterator);
    return node->next;
}

iterator_t list_get_previous(iterator_t iterator)
{
    if (iterator == NULL)
        return NULL;
    struct _private_list_node *node = TO_NODE(iterator);
    return node->prev;
}

void *list_get_element(iterator_t iterator)
{
    if (iterator == NULL)
        return NULL;
    struct _private_list_node *node = TO_NODE(iterator);
    return node->element;
}

int list_add_element(list_t list, void *element)
{
    if (list == NULL)
        return -1;

    struct _private_list *l = TO_LIST(list);

    if (l->size == l->capacity)
        return -1;
    unsigned *free_node_index = queue_dequeue(l->free_nodes);
    if (free_node_index == NULL)
    {
        return -1;
    }

    struct _private_list_node *node = &l->nodes[*free_node_index];

    if (l->head == NULL)
    {
        l->head = node;
    }

    if (l->tail == NULL)
    {
        l->tail = node;
    }
    else
    {
        l->tail->next = node;
        node->prev = l->tail;
        l->tail = node;
    }
    
    memcpy(node->element, (__uint8_t*)element, l->element_size);
    l->size++;

    return 0;
}

void list_remove_element(list_t list, iterator_t *iterator)
{
    if (list == NULL)
        return;
    if (iterator == NULL)
        return;

    struct _private_list *l = TO_LIST(list);
    struct _private_list_node *node = TO_NODE(*iterator);

    if (l->head == node)
    {
        l->head = node->next;
    }

    if (l->tail == node)
    {
        l->tail = node->prev;
    }

    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }

    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }

    node->next = NULL;
    node->prev = NULL;
    unsigned node_index = node - l->nodes;
    queue_enqueue(l->free_nodes, &node_index);
    *iterator = NULL;
    l->size--;
}
