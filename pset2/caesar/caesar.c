#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("ERROR: Must enter a single key to continue.\n");
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);
        string p = get_string("plaintext: ");
        printf("ciphertext: ");
        int ci, pi;
        char c;
        for (int i = 0; i < strlen(p); i++)
        {
            pi = (int) p[i];
            if (pi > 96 && pi < 123)
            {
                pi = pi - 97;
                ci = (pi + k) % 26 + 97;
                c = (char) ci;
                printf("%c", c);
            }
            else if (pi > 64 && pi < 91)
            {
                pi = pi - 65;
                ci = (pi + k) % 26 + 65;
                c = (char) ci;
                printf("%c", c);
            }
            else
            {
                printf("%c", p[i]);
            }
        }
        printf("\n");
    }
}