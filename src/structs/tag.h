/* tag.h */

#pragma once 

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

typedef struct Tag
{
    char *filename;                                                                            
    char *title;
    char *artist;
    char *album;
    char *track_num;
    char *year;
    char *genre;
} Tag;

Tag *create_tag(const char *filename, const char *title, const char *artist, const char *album, 
                const char *track_num, const char *year, const char *genre);
void delete_tag(Tag *tag);
