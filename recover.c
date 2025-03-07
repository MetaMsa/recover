#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");

        return 1;
    }

    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    int i = 0;

    unsigned char buffer[512];

    FILE *img = NULL;

    while (fread(buffer, 512, 1, inptr) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
                fclose(img);

            char filename[10];

            sprintf(filename, "%03i.jpg", i);

            img = fopen(filename, "w");

            i++;
        }
        if (img != NULL)
            fwrite(buffer, 512, 1, img);
    }

    if (img != NULL)
            fclose(img);

    fclose(inptr);

    return 0;
}