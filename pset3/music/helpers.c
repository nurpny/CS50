// Helper functions for music

#include <cs50.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    float n = fraction[0] - '0';
    float d = fraction[2] - '0';
    float x = 1.0*(n/d)/(1.0/8.0);
    return round(x);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    int oct = note[strlen(note)-1] - '0';
    float x = 12 * (oct-4);
    switch (note[0])
    {
        case 'C':
            x -=9;
            break;
        case 'D':
            x -=7;
            break;
        case 'E':
            x -=5;
            break;
        case 'F':
            x -=4;
            break;
        case 'G':
            x -=2;
            break;
        case 'B':
            x += 2;
            break;
    }
    if (note[1] == '#'){
        x++;
    }
    else if (note[1] == 'b'){
        x--;
    }
    return round(440*pow(2,x/12));
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if (s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}
