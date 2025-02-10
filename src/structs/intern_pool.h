#pragma once
#include "hash.h"


#define POOL_SIZE 1024

typedef struct StringEntry
{
    char *string;
    struct StringEntry *next;
} StringEntry;

typedef struct InternPool
{
    StringEntry *Buckets[POOL_SIZE];

} InternPool;

InternPool *intern_pool;

void init_intern_pool();

const char* intern_string(const char *str);

void delete_intern_pool();

void test_intern_pool();