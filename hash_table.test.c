#include <stdio.h>

#include "tester/tester.h"
#include "quicker/hash_table.h"

int main(int argc, char *argv[])
{
    int capacity = 225;
    hash_table_t table = ht_create(capacity, sizeof(int));
    ASSERT_IS_NOT_NULL(table, "%s" ,"Create hash table success");

    int ht_capacity = ht_get_capacity(table);
    ASSERT_IS_EQUAL(capacity, ht_capacity, "Capacity in table: %d, expected: %d", ht_capacity, capacity);

    int ht_count = ht_get_count(table);
    ASSERT_IS_EQUAL(0, ht_count, "Count in table: %d, expected: %d", ht_count, 0);

    const char* keys[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *value = NULL;

    for (int i = 0; i < 10; i++){
        int is_collision = ht_set(table, keys[i], &values[i]);
        ASSERT_IS_TRUE(! is_collision, "No collision for key \"%s\"", keys[i]);

        ht_count = ht_get_count(table);
        ASSERT_IS_EQUAL(i + 1, ht_count, "Count in table: %d, expected: %d", ht_count, i + 1);
        
        value = ht_get(table, keys[i]);
        ASSERT_IS_NOT_NULL(value, "Get value for key \"%s\" success", keys[i]);
        ASSERT_IS_EQUAL(values[i], *value, "Value in table: %d, expected: %d", *value, values[i]);
    }

    value = ht_get(table, "ten");
    ASSERT_IS_NOT_NULL(value, "Value for key \"ten\" is %d", *value);

    value = ht_get(table, "eleven");
    ASSERT_IS_NULL(value, "%s", "Value for key \"eleven\" is NULL");

    ht_destroy(&table);
    ASSERT_IS_NULL(table, "%s" ,"Destroy hash table success");

    value = ht_get(table, "ten");
    ASSERT_IS_NULL(value, "%s", "Value for key \"ten\" is NULL after destroy");

    printf("All tests passed\n");

    return 0;
}
