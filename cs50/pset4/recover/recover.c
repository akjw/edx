#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error: File could not be opened\n");
        return 1;
    }

    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    size_t bytes_remaining;
    bool is_first = false;
    FILE *current_file;
    char new_file_name[100];
    int current_num = 0;
    bool alr_found = false;

    while (true)
    {
        // fread returns bytes left to read
        bytes_remaining = fread(buffer, sizeof(BYTE), BLOCK_SIZE, file);
        if (bytes_remaining == 0)
        {
            break;
        }

        // check for jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            alr_found = true;
            if (!is_first)
            {
                is_first = true;
            }
            else
            {
                fclose(current_file);
            }
            sprintf(new_file_name, "%03i.jpg", current_num);
            current_file = fopen(new_file_name, "w");
            fwrite(buffer, sizeof(BYTE), bytes_remaining, current_file);
            current_num++;
        }
        else
        {
            if (alr_found)
            {
                fwrite(buffer, sizeof(BYTE), bytes_remaining, current_file);
            }
        }
    }
    fclose(file);
    fclose(current_file);
    return 0;
}
