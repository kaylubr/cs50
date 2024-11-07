#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Open memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Error! File cannot be opened\n");
        return 2;
    }

    // Buffer to store the bytes
    BYTE buffer[512];

    char filename[8];
    int counter = 0;

    FILE *img = NULL;
    while (fread(buffer, sizeof(BYTE), 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img == NULL)
            {
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
            counter++;
        }
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
}
