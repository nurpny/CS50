#include <stdio.h>
#include <stdint.h>
#include <cs50.h>

int main(int argc, char *argv[]){

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: input a file to retcover JPEGs from\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // declare block array of 512 bytes and file name
    int n = 0;
    char filename[8];
    FILE *img = NULL;

    int end = 0;

    while (end==0)
    {
        //initiate an array of 512 bytes
        uint8_t buffer[512];

        // if fread returns value less than 512 the file is at the end.
        int x = fread(buffer, 1, 512, inptr);
        if (x < 512)
            end = 1;

        // check for jpeg in the first 4 bytes of jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // if there was a preexisting img file open, close it
                if (img != NULL)
                    fclose(img);

                // open new file name then write in it.
                sprintf(filename, "%03i.jpg", n);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(buffer), 1, img);
                n++;
            }
        // until new JPEG header is found, continue writing in the opened img file
        else
        {
            if (img != NULL)
                fwrite(buffer, x, 1, img);
        }
    }

    // error msg if no JPEG images have been found. if no error, close the last opened img file
    if (img == NULL)
    {
        fprintf(stderr, "No jpeg files recovered.\n");
        return 3;
    }
    else
    {
        fclose(img);
    }

    //close input file
    fclose(inptr);
}