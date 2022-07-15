#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define BLOCK_SIZE 512

uint8_t buffer[BLOCK_SIZE];

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r");
    bool writing = false;
    int writing_to = 0;
    char filename[10];
    sprintf(filename, "%03i.jpg", 0);
    FILE *output = fopen(filename, "w");
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (!writing)
            {
                writing = true;
            }
            else
            {
                //fclose(output);
                writing_to++;
                sprintf(filename, "%03i.jpg", writing_to);
                output = fopen(filename, "w");
            }
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
        else if (writing)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
    }
    fclose(output);
    fclose(raw_file);
}