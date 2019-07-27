/******
 * resize.c
 * Resize a bmp file by a factor of n
*******/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy <n factor> <infile> <outfile>\n");
        return 1;
    }

    // ensure that factor integer greater between 1 and 100 is entered.
    int n = atoi(argv[1]);
    if (n > 100 || n < 1)
    {
        fprintf(stderr, "Usage: enter n between 1 and 100.\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding from the input file
    int padding1 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // resize BITMAPINFOHEADER
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine the new padding
    int padding2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine the new image size
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding2) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight)/n; i < biHeight; i++)
    {
        // iterate over each line n factor times
        for (int l = 0; l < n; l++)
        {
            // iterate over pixels in scanline
            for (int j = 0, biWidth = bi.biWidth/n; j < biWidth; j++)
            {

                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int m = 0; m < n; m++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
             }
            // add new padding calculation to the output, if any
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }

            // point back one line in the input until the last line
            if (l < (n - 1))
                fseek(inptr, -(bi.biWidth/n)*sizeof(RGBTRIPLE), SEEK_CUR);
        }
         // skip over padding in input, if any
         fseek(inptr, padding1, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
