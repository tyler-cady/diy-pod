#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intern_pool.h"


void init_intern_pool()
{
    intern_pool = (InternPool *)malloc(sizeof(InternPool));
    for (int i = 0; i < POOL_SIZE; i++)
        intern_pool->Buckets[i] = NULL;
}

const char* intern_string(const char *str)
{
    // Ensure intern_pool is initialized
    if (intern_pool == NULL) {
        // Handle the error (perhaps initialize intern_pool here)
        return NULL;
    }

    unsigned int idx = hash_pjw(str) % POOL_SIZE;
    StringEntry *entry = intern_pool->Buckets[idx];

    while (entry)
    {
        if (strcmp(entry->string, str) == 0)
            return entry->string;
        entry = entry->next;
    }

    // New string -- Intern It!
    StringEntry *new = (StringEntry *)malloc(sizeof(StringEntry));
    if (new == NULL) {
        return NULL;  // Handle memory allocation failure
    }

    new->string = strdup(str);
    if (new->string == NULL) {
        free(new);
        return NULL;  // Handle string duplication failure
    }

    new->next = intern_pool->Buckets[idx];
    intern_pool->Buckets[idx] = new;

    return new->string;
}


void delete_intern_pool()
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        StringEntry *entry = intern_pool->Buckets[i];
        while (entry)
        {
            StringEntry *temp = entry;
            entry = entry->next;
            free(temp->string);
            free(temp);
        }
    }
    free(intern_pool);
}

void test_intern_pool()
{
    // Initialize the intern pool
    init_intern_pool();

    // Test intern_string for unique strings
    const char *str1 = "Hello, World!";
    const char *str2 = "Goodbye, World!";
    const char *str3 = "Hello, World!"; // Should match str1
    const char *str4 = "New String";

    const char *result1 = intern_string(str1);
    const char *result2 = intern_string(str2);
    const char *result3 = intern_string(str3);
    const char *result4 = intern_string(str4);

    // Output the results to ensure they are interned properly
    printf("Result 1: %s\n", result1);
    printf("Result 2: %s\n", result2);
    printf("Result 3 (should match Result 1): %s\n", result3);
    printf("Result 4: %s\n", result4);

    // Check if interned strings are duplicates
    if (result1 == result3)
    {
        printf("Test Passed: Duplicates interned correctly for \"%s\".\n", str1);
    }
    else
    {
        printf("Test Failed: Duplicate strings not interned correctly.\n");
    }

    // Cleanup the intern pool
    delete_intern_pool();
}

// int main()
// {
//     // Run the test for the intern pool
//     test_intern_pool();
//     return 0;
// }
