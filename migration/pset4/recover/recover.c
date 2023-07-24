#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw");
        return 1;
    }


    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 2;
    }

    unsigned char buffer[512];

    int count_image = 0;


    FILE *output_file = NULL;
    char *filename = malloc(8 * sizeof(char));

    while (fread(buffer, sizeof(char), 512, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //write jpeg into file name in form 001.jpg, 002.jpg and so on
            sprintf(filename, "%03i.jpg", count_image);

            //open Out_file for writing
            output_file = fopen(filename, "w");

            //fwrite(buffer, sizeof(buffer), 1, output_file);
            //count number of image found
            count_image++;
        }
        //Check if output have been used for valid input
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output_file);
        }
    }
    free(filename);
    fclose(output_file);
    fclose(file);

    return 0;
}