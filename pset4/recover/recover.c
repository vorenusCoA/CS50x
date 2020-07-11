#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover fileName\n");
        return 1;
    }

    // Try to open the file
    FILE *imageRaw = fopen(argv[1], "r");
    if (imageRaw == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    char *newFileName = malloc((8) * sizeof(char)); // 1 byte ###.jpg
    FILE *newFile = NULL;
    int filesCreated = 0;
    bool writingFile = false;
    // Read the whole memory card
    while (true)
    {
        // We read 512 into a buffer
        int bytesRead = fread(buffer, 1, sizeof buffer, imageRaw);

        // Check for a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If we are writing we have to close the actual file and make a new one
            if (writingFile)
            {
                fclose(newFile);
            }

            // Create a new file
            sprintf(newFileName, "%03i.jpg", filesCreated);
            newFile = fopen(newFileName, "w");
            filesCreated++;
            fwrite(buffer, bytesRead, 1, newFile);
            writingFile = true;
        }
        else
        {
            // Continue writing
            if (writingFile)
            {
                fwrite(buffer, bytesRead, 1, newFile);
            }
        }

        // If we get less than 512 we are at EOF
        if (bytesRead < 512)
        {
            fclose(imageRaw);
            fclose(newFile);
            break;
        }
    }

    // Release memory
    free(newFileName);

    return 0;
}
