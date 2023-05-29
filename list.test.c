#include <stdio.h>

#include "tester/tester.h"
#include "quicker/list.h"

#define TEST_SIZE 10

int main()
{
    list_t list = list_create(sizeof(int), TEST_SIZE);
    MSG_INFO_DEBUG("Creating list with size: %d", TEST_SIZE);
    ASSERT_IS_NOT_NULL(list, "%s", "Creating list");

    MSG_INFO_DEBUG("%s","Adding elements to list");
    for (int i = 0; i < TEST_SIZE / 2; i++)
    {
        int result = list_add_element(list, &i);
        ASSERT_IS_EQUAL(result, 0, "Adding element \"%d\" to list", i);
        int size = list_get_size(list);
        ASSERT_IS_EQUAL(size, i + 1, "List size expected:  %d, actual: %d", i + 1, size);
    }

    for (int i = 0; i < TEST_SIZE; i++)
    {
        int result = list_add_element(list, &i);
        if (i < TEST_SIZE / 2)
        {
            ASSERT_IS_EQUAL(result, 0, "Adding element \"%d\" to list", i);
            int size = list_get_size(list);
            ASSERT_IS_EQUAL(size, i + 1 + TEST_SIZE / 2, "List size expected:  %d, actual: %d", i + 1 + TEST_SIZE / 2, size);
        }
        else
        {
            ASSERT_IS_NOT_EQUAL(result, 0, "Can not add element \"%d\" to full list", i);
            int size = list_get_size(list);
            ASSERT_IS_EQUAL(size, TEST_SIZE, "List size expected:  %d, actual: %d", TEST_SIZE, size);
        }
    }

    MSG_INFO_DEBUG("%s","Checking iterators order");

    iterator_t begin = list_begin(list);
    ASSERT_IS_NOT_NULL(begin, "%s", "Getting list begin iterator");

    iterator_t end = list_end(list);
    ASSERT_IS_NOT_NULL(end, "%s", "Getting list end iterator");

    for (int i = 1; i < TEST_SIZE; i++)
    {
        begin = list_get_next(begin);
        ASSERT_IS_NOT_NULL(begin, "Getting next iterator for element index: %d", i);
    }

    ASSERT_IS_EQUAL(begin, end, "List end iterator is equal to iterator on index %d", TEST_SIZE - 1);

    MSG_INFO_DEBUG("%s","Checking list elements");
    int expected_raw[TEST_SIZE] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
    int *pexpected = expected_raw;
    for (iterator_t it = list_begin(list); it != NULL; it = list_get_next(it))
    {
        ASSERT_IS_NOT_NULL(it, "%s", "Getting iterator from list");
        int *element = list_get_element(it);
        ASSERT_IS_NOT_NULL(element, "%s", "Getting element from list");
        ASSERT_IS_EQUAL(*element, *pexpected, "Expected element: %d, actual: %d", *pexpected, *element);
        pexpected++;
    }

    MSG_INFO_DEBUG("%s","Checking list removing elements");
    int expected_new[TEST_SIZE - 3] = {1, 2, 4, 0, 1, 2, 3};
    pexpected = expected_new;
    iterator_t it = list_begin(list);
    int *element = list_get_element(it);
    ASSERT_IS_NOT_NULL(element, "%s", "Getting first element from list");
    ASSERT_IS_EQUAL(*element, 0, "Expected element: %d, actual: %d", 0, *element);
    iterator_t next = list_get_next(it);
    it = list_remove_element(list, it);
    ASSERT_IS_EQUAL(next, it, "%s", "Clear iterator after removing element" );
    
    it = list_begin(list);
    ASSERT_IS_NOT_NULL(element, "%s", "Getting first element from list");
    element = list_get_element(it);
    ASSERT_IS_EQUAL(*element, *pexpected, "Expected element: %d, actual: %d", *pexpected, *element);

    it = list_get_next(it);
    it = list_get_next(it);
    element = list_get_element(it);
    ASSERT_IS_EQUAL(*element, expected_raw[3], "Expected element: %d, actual: %d", expected_raw[3], *element);
    next = list_get_next(it);
    it = list_remove_element(list, it);
    ASSERT_IS_EQUAL(next, it, "%s", "Clear iterator after removing element" );
    it = list_end(list);
    element = list_get_element(it);
    ASSERT_IS_EQUAL(*element, expected_raw[TEST_SIZE -1], "Expected element: %d, actual: %d", expected_raw[TEST_SIZE - 1], *element);
    list_remove_element(list, it);
    ASSERT_IS_EQUAL(list_get_size(list), TEST_SIZE - 3, "Expected size: %d, actual: %d", TEST_SIZE - 3, list_get_size(list));

    for (iterator_t it = list_begin(list); it != NULL; it = list_get_next(it))
    {
        ASSERT_IS_NOT_NULL(it, "%s", "Getting iterator from list");
        int *element = list_get_element(it);
        ASSERT_IS_NOT_NULL(element, "%s", "Getting element from list");
        ASSERT_IS_EQUAL(*element, *pexpected, "Expected element: %d, actual: %d", *pexpected, *element);
        pexpected++;
    }

    for(iterator_t it = list_begin(list); it != NULL;)
    {
        it = list_remove_element(list, it);
    }
    ASSERT_IS_EQUAL(list_get_size(list), 0, "Expected size: %d, actual: %d", 0, list_get_size(list));


    MSG_INFO_DEBUG("%s","Destroying list");
    list_destroy(&list);
    ASSERT_IS_NULL(list, "%s", "Destroying list");
}