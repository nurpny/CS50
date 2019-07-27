#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // checks for a single key
    if (argc != 2)
    {
        printf("ERROR: Must enter a single key to continue.\n");
        return 1;
    }
    else
    {
        //set key array
        int keys[strlen(argv[1])];
        int k;
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            k = (int) argv[1][j];
            // if character in the key is not alphabetical, throw an error msg.
            if (k > 122 || k < 65 || (k > 90 && k < 97))
            {
                printf("ERROR: Must enter a single key with alphabet only to continue.\n");
                return 1;
                break;
            }
            else if (k > 96)
            {
                keys[j] = k - 97;
            }
            else
            {
                keys[j] = k - 65;
            }
        }


        string p = get_string("plaintext: ");
        printf("ciphertext: ");
        int ci, pi;
        int j = 0;
        char c;
        for (int i = 0; i < strlen(p); i++)
        {
            // j index for key array is reset if it exceeds the length of the array
            if (j == sizeof(keys) / sizeof(int))
            {
                j = 0;
            }
            pi = (int) p[i];
            if (pi > 96 && pi < 123)
            {
                pi = pi - 97;
                ci = (pi + keys[j]) % 26 + 97;
                c = (char) ci;
                printf("%c", c);
                j++;
            }
            else if (pi > 64 && pi < 91)
            {
                pi = pi - 65;
                ci = (pi + keys[j]) % 26 + 65;
                c = (char) ci;
                printf("%c", c);
                j++;
            }
            else
            {
                printf("%c", p[i]);
            }
        }
        printf("\n");
    }
}