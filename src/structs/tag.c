#include "tag.h"

Tag *create_tag(const char *filename, const char *title, const char *artist, const char *album, 
                const char *track_num, const char *year, const char *genre)
{
    Tag *t = (Tag *)malloc(sizeof(*t));
    if (!t) {
        fprintf(stderr, "Allocation Error: TAG\n");
        return NULL;
    }
    // t->filename = filename   ? strdup(filename) : NULL;
    // t->title = title         ? strdup(title)    : NULL;
    // t->artist = artist       ? strdup(artist)   : NULL;
    // t->album = album         ? strdup(album)    : NULL;
    // t->track_num = track_num ? strdup(track_num): NULL;
    // t->year = year           ? strdup(year)     : NULL;
    // t->genre = genre         ? strdup(genre)    : NULL;


    t->filename = filename   ? intern_string(filename) : (const char *)NULL;
    t->title = title         ? intern_string(title)    : (const char *)NULL;
    t->artist = artist       ? intern_string(artist)   : (const char *)NULL;
    t->album = album         ? intern_string(album)    : (const char *)NULL;
    t->track_num = track_num ? intern_string(track_num): (const char *)NULL;
    t->year = year           ? intern_string(year)     : (const char *)NULL;
    t->genre = genre         ? intern_string(genre)    : (const char *)NULL;
    
    return t;
}

void delete_tag(Tag *t)
{
    if (t) {
        // free(t->filename);
        // free(t->title);
        // free(t->artist);
        // free(t->album);
        // free(t->track_num);
        // free(t->year);
        // free(t->genre);
        free(t); // Free the struct itself
    }
}
