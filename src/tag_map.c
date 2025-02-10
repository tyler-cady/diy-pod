#include "tag_map.h"


int is_mp3(const char *filename)
{
    const char *ext = strchr(filename, '.');
    return ext && (strcasecmp(ext, ".mp3") == 0);
}

void read_dir_mp3(OuterMap *outerMap,  const char *path)
{
    
}