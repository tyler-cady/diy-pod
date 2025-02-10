#pragma once

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tag.h"

/* Forward Declarations */
typedef struct OuterMap OuterMap;
typedef struct OuterEntry OuterEntry;
typedef struct InnerMap InnerMap;
typedef struct InnerEntry InnerEntry;

/* Outer Map */
typedef struct OuterMap
{
    int size;
    OuterEntry **bucket;
} OuterMap;

typedef struct OuterEntry
{
    char *meta_type; /* album, artist, title, genre, year */
    InnerMap *innerMap;
    struct OuterEntry *next;
} OuterEntry;

OuterMap *create_OuterMap(int size);

/* Inner Map */
typedef struct InnerMap
{
    int size;
    InnerEntry **bucket;
} InnerMap;

typedef struct InnerEntry
{
    char *key; /* Changed from char to char* */
    Tag *tag;
    struct InnerEntry *next;
} InnerEntry;

InnerMap *create_InnerMap(int size);

/* Insert Functions  */
void outerInsert(OuterMap *map, const char *meta_type, InnerMap *innerMap);
void innerInsert(InnerMap *map, const char *key, Tag *tag);

/* Constructors */
OuterMap *create_OuterMap(int size);
InnerMap *create_InnerMap(int size);

/* Destructors */
void deleteOuterMap(OuterMap *map);
void deleteInnerMap(InnerMap *map);

/* Hash Function */
int hash_pjw(const char *key);