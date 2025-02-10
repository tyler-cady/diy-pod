#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "structs/tag.h"

#define ID3_HEADER_SIZE 10
#define ID3_FRAME_HEADER_SIZE 10


int id3_get_size(unsigned char *bytes);
char *utf16_to_utf8(unsigned char *data, int size);
char *id3_read_text_frame(FILE *file, int frame_size);

Tag *read_id3v2(const char *filename);
