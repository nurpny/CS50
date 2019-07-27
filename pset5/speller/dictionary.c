// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"

#define BASE (256)
#define PRIME (59)


// Define node structure
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// create a hashtable with linked lists.
node *hashtable[59];

void hasht_init(void)
{

    for (int i = 0; i< PRIME; i++)
    {
        hashtable[i]=NULL;
    }
}



// hash function
// http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
unsigned long
hash(char arr[])
{
    unsigned long h = 0;
    int i = 0;

    while(arr[i] != '\0') {
        h = (h * BASE + arr[i]) % PRIME;
        i++;
    }
    return h;
}


// Returns true if word is in dictionary else false
bool check(const char *inputword)
{
    // turn inputword into lowercase
    char lword [LENGTH+1]={0};
    strcpy (lword, inputword);
    for (int i = 0; i < LENGTH; i++)
        {
            lword[i] = tolower (lword[i]);
        }


    bool result = false;

    // find the value after running the word through hashfunction;
    int h = hash(lword);

    // return true if match found in the linked list indexed by the hash value
    for (node *ptr = hashtable[h]; ptr != NULL; ptr = ptr->next)
    {
        if (strcmp (ptr->word, lword)==0)
        {
            result = true;
            break;
        }
    }
    return result;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char rword[LENGTH+1]={0};
    // open dictionary
    FILE *dict_inptr = fopen(dictionary, "r");

    // scan dictionary word by word
    while (fscanf(dict_inptr, "%s", rword) != EOF)
    {

        //malloc a node *for each node
        node *new_node = malloc(sizeof(node));

        // in case of no memory left, unload.
        if (new_node == NULL)
        {
            unload();
            return false;
            break;
        }

        else
        {
            // else copy word into node
            strcpy (new_node->word, rword);
            new_node-> next = NULL;

            // find hashvalue from the hash function
            int hashval = hash(rword);

            // if hashed linked list is empty, the new node is the first node of the linked list;
            if (hashtable[hashval] == NULL)
            {
                hashtable[hashval] = new_node;
            }
            // else insert into a linked list
            else
            {
                new_node->next = hashtable[hashval];
                hashtable[hashval] = new_node;
            }
        }
    }
    fclose(dict_inptr);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0; i < PRIME; i++)
    {
        node *ptr = hashtable[i];
        while (ptr != NULL)
        {
            count++;
            node *next = ptr->next;
            ptr = next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < PRIME; i++)
    {
        node *ptr = hashtable[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}

