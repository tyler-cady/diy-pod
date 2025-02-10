#include "tag_map.h"
#include "tag_ripper.h"


int is_mp3(const char *filename)
{
    const char *ext = strchr(filename, '.');
    return ext && (strcasecmp(ext, ".mp3") == 0);
}

void rip_tags_dir(char *dir)
{
    DIR *dp = opendir(dir);
    if(!dp)
    {
        fprintf(stderr, "Error: Unable to open directory %s\n", dir);
        return;
    }

    struct dirent *entry;
    for (entry = readdir(dp); entry; entry = readdir(dp))
    {
        if (entry->d_type == DT_REG && is_mp3(entry->d_name))
        {
            char path[PATH_MAX];
            snprintf(path, PATH_MAX, "%s/%s", dir, entry->d_name);
            Tag *tag = read_id3v2(path);
            if (tag)
            {
                printf("\nFile: %s\n", tag->filename);
                printf("Title: %s\n", tag->title ? tag->title : "N/A");
                printf("Artist: %s\n", tag->artist ? tag->artist : "N/A");
                printf("Album: %s\n", tag->album ? tag->album : "N/A");
                printf("Track: %s\n", tag->track_num ? tag->track_num : "N/A");
                printf("Year: %s\n", tag->year ? tag->year : "N/A");
                printf("Genre: %s\n", tag->genre ? tag->genre : "N/A");

                delete_tag(tag);
            }
        }
    }
}

int main()
{
    rip_tags_dir("mp3");
    return 0;
}