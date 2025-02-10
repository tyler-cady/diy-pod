#include "tag_ripper.h"



// Reads a 4-byte syncsafe integer from ID3v2.4+ frames
int id3_get_size(unsigned char *bytes)
{
    return (bytes[0] << 21) | (bytes[1] << 14) | (bytes[2] << 7) | bytes[3];
}

// Converts UTF-16 to UTF-8
char *utf16_to_utf8(unsigned char *data, int size)
{
    if (size < 2)
        return NULL;

    // Check BOM (Byte Order Mark)
    int is_little_endian = (data[0] == 0xFF && data[1] == 0xFE);
    int is_big_endian = (data[0] == 0xFE && data[1] == 0xFF);

    if (!is_little_endian && !is_big_endian)
    {
        printf("Unknown UTF-16 byte order.\n");
        return NULL;
    }

    // Skip BOM
    data += 2;
    size -= 2;

    // Allocate memory for UTF-8 conversion (at most 3 bytes per UTF-16 char)
    char *utf8_str = (char *)malloc(size * 3);
    if (!utf8_str)
        return NULL;

    char *out = utf8_str;
    for (int i = 0; i < size; i += 2)
    {
        unsigned short codepoint;
        if (is_little_endian)
        {
            codepoint = data[i] | (data[i + 1] << 8);
        }
        else
        {
            codepoint = (data[i] << 8) | data[i + 1];
        }

        if (codepoint < 0x80)
        {
            *out++ = codepoint;
        }
        else if (codepoint < 0x800)
        {
            *out++ = 0xC0 | (codepoint >> 6);
            *out++ = 0x80 | (codepoint & 0x3F);
        }
        else
        {
            *out++ = 0xE0 | (codepoint >> 12);
            *out++ = 0x80 | ((codepoint >> 6) & 0x3F);
            *out++ = 0x80 | (codepoint & 0x3F);
        }
    }

    *out = '\0'; // Null-terminate the UTF-8 string
    return utf8_str;
}

// Reads text frame data and handles encoding
char *id3_read_text_frame(FILE *file, int frame_size)
{
    if (frame_size <= 1)
        return NULL;

    unsigned char encoding;
    fread(&encoding, 1, 1, file); // Read encoding byte

    unsigned char *data = (unsigned char *)malloc(frame_size - 1);
    if (!data)
        return NULL;

    fread(data, 1, frame_size - 1, file);

    // Handle encoding cases
    char *result = NULL;
    if (encoding == 0x00 || encoding == 0x03)
    {
        // ISO-8859-1 or UTF-8 (already fine in C)
        result = (char *)data;
    }
    else if (encoding == 0x01)
    {
        // UTF-16 (convert to UTF-8)
        result = utf16_to_utf8(data, frame_size - 1);
        free(data); // Free UTF-16 data after conversion
    }
    else
    {
        printf("Unsupported encoding: %02X\n", encoding);
        free(data);
    }

    return result;
}

Tag *read_id3v2(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    unsigned char header[ID3_HEADER_SIZE];
    fread(header, 1, ID3_HEADER_SIZE, file);

    if (memcmp(header, "ID3", 3) != 0)
    {
        fprintf(stderr, "Not a valid ID3v2 file.\n");
        fclose(file);
        return NULL;
    }

    int tag_size = id3_get_size(&header[6]);
    printf("ID3 Tag Size: %d bytes\n", tag_size);

    Tag *tag = (Tag *)calloc(1, sizeof(Tag));
    if (!tag)
    {
        fclose(file);
        return NULL;
    }

    tag->filename = strdup(filename);

    while (ftell(file) < tag_size + ID3_HEADER_SIZE)
    {
        unsigned char frame_header[ID3_FRAME_HEADER_SIZE];
        if (fread(frame_header, 1, ID3_FRAME_HEADER_SIZE, file) != ID3_FRAME_HEADER_SIZE)
        {
            break;
        }

        if (frame_header[0] == 0)
            break; // Padding reached

        int frame_size = id3_get_size(&frame_header[4]);
        printf("Frame ID: %.4s | Frame Size: %d bytes\n", frame_header, frame_size);

        if (strncmp((char *)frame_header, "TIT2", 4) == 0)
        {
            tag->title = id3_read_text_frame(file, frame_size);
        }
        else if (strncmp((char *)frame_header, "TPE1", 4) == 0)
        {
            tag->artist = id3_read_text_frame(file, frame_size);
        }
        else if (strncmp((char *)frame_header, "TALB", 4) == 0)
        {
            tag->album = id3_read_text_frame(file, frame_size);
        }
        else if (strncmp((char *)frame_header, "TRCK", 4) == 0)
        {
            tag->track_num = id3_read_text_frame(file, frame_size);
        }
        else if (strncmp((char *)frame_header, "TYER", 4) == 0)
        {
            tag->year = id3_read_text_frame(file, frame_size);
        }
        else if (strncmp((char *)frame_header, "TCON", 4) == 0)
        {
            tag->genre = id3_read_text_frame(file, frame_size);
        }
        else
        {
            fseek(file, frame_size, SEEK_CUR); // Skip unknown frame
        }
    }

    fclose(file);
    return tag;
}



// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//     {
//         fprintf(stderr, "Usage: %s <mp3 file>\n", argv[0]);
//         return 1;
//     }

//     Tag *tag = read_id3v2(argv[1]);
//     if (tag)
//     {
//         printf("\nFile: %s\n", tag->filename);
//         printf("Title: %s\n", tag->title ? tag->title : "N/A");
//         printf("Artist: %s\n", tag->artist ? tag->artist : "N/A");
//         printf("Album: %s\n", tag->album ? tag->album : "N/A");
//         printf("Track: %s\n", tag->track_num ? tag->track_num : "N/A");
//         printf("Year: %s\n", tag->year ? tag->year : "N/A");
//         printf("Genre: %s\n", tag->genre ? tag->genre : "N/A");

//         delete_tag(tag);
//     }

//     return 0;
// }
