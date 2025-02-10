#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <sys/stat.h>

#include "structs/map.h"
#include "structs/tag.h"


#define PATH_MAX 4096

int is_mp3(const char *filename);
void read_dir_mp3(OuterMap *outerMap, const char *path);
