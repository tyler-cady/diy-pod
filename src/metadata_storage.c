#include "metadata_storage.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Insert Functions  */
void outerInsert(OuterMap *map, const char *meta_type, InnerMap *innerMap)
{
    int hash_val = hash_pjw(meta_type);
    int idx = hash_val % map->size;

    OuterEntry *entry = malloc(sizeof(OuterEntry));
    assert(entry != NULL);
    if (!entry)
        return;

    entry->meta_type = strdup(meta_type);
    entry->innerMap = innerMap;
    entry->next = map->bucket[idx];
    map->bucket[idx] = entry;
}

void innerInsert(InnerMap *map, const char *key, Tag *tag)
{
    int hash_val = hash_pjw(key);
    int index = hash_val % map->size;
    InnerEntry *entry = malloc(sizeof(InnerEntry));
    assert(entry != NULL);
    if (!entry)
        return;

    entry->key = strdup(key); // Now valid, since key is a char*
    entry->tag = tag;
    entry->next = map->bucket[index];
    map->bucket[index] = entry;
}

/* Constructors */
OuterMap *create_OuterMap(int size)
{
    OuterMap *map = malloc(sizeof(OuterMap));
    if (!map)
        return NULL;
    map->size = size;
    map->bucket = calloc(size, sizeof(OuterEntry *));
    if (!map->bucket)
    {
        free(map);
        return NULL;
    }
    return map;
}

InnerMap *create_InnerMap(int size)
{
    InnerMap *map = malloc(sizeof(InnerMap));
    if (!map)
        return NULL;

    map->size = size;
    map->bucket = calloc(size, sizeof(InnerEntry *));
    if (!map->bucket)
    {
        free(map);
        return NULL;
    }
    return map;
}

/* Destructors */
void deleteOuterMap(OuterMap *map)
{
    assert(map != NULL);
    for (int i = 0; i < map->size; i++)
    {
        OuterEntry *entry = map->bucket[i];
        while (entry)
        {
            OuterEntry *temp = entry;
            entry = entry->next;
            free(temp->meta_type);
            deleteInnerMap(temp->innerMap);
            free(temp);
        }
    }
    free(map->bucket);
    free(map);
}

void deleteInnerMap(InnerMap *map)
{
    assert(map != NULL);
    for (int i = 0; i < map->size; i++)
    {
        InnerEntry *entry = map->bucket[i];
        while (entry)
        {
            InnerEntry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp->tag);
            free(temp);
        }
    }
    free(map->bucket);
    free(map);
}

/* Hash Function */
int hash_pjw(const char *key)
{
    const char *ptr = key;
    unsigned int val = 0;
    while (*ptr != '\0')
    {
        unsigned int tmp;
        val = (val << 4) + (*ptr);
        if ((tmp = (val & 0xf0000000)))
        {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }
        ptr++;
    }
    return val;
}

void list_albums(OuterMap *map)
{
    /* alphabetically sort albums by name with merge sort */
    
}

int main()
{
    return 0;
}
