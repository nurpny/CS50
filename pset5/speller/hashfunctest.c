#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BASE (256)

unsigned long
hash(char arr[])
{
    printf("first letter: c: %c", arr[0]);
    unsigned long h = 0;
    int i = 0;

    while(arr[i] != '\0') {
        h = (h * BASE + arr[i]) % 59; /* 59 is a prime number used in this particular case */
        i++;
    }
    printf("h: %ld\n", h);
    return h;
}


int main(void)
{
    hash("caterpillar");

}

