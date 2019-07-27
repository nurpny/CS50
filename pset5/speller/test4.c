#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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

bool check(const char *inputword)
{
    // turn inputword into lowercase
    char lword [LENGTH+1]={0};
    strcpy (lword, inputword);

    /* need to copy to char * from const char */
    for (int i = 0; i < LENGTH; i++)
        {
            lword[i] = tolower (lword[i]);
        }
    printf("lower string: [%s], stlen: %lu\n", lword, strlen(lword));

    printf("print lword by characters: ");
    for (int i = 0; i < LENGTH+1; i++)
        {
            printf("%c", lword[i]);
        }
    printf("\n");

    bool result = false;
    // find the value after running the word through hashfunction;
    int h = hash(lword);
    printf("hash #: %i\n", h);
    int counter = 0;
    // return true if match found in the linked list indexed by the hash value
    for (node *ptr = hashtable[h]; ptr != NULL; ptr = ptr->next)
    {
        printf("at hash #: %i and counter # %i.word is: %s. strlen: %lu\n", h, counter, ptr->word, strlen(ptr->word));
        if (strcasecmp (ptr->word, lword)==0)
        {
            result = true;
            printf("TRUE!\n");
            break;
        }
    }
    return result;
}


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
        printf("malloc. new_node value is: %p: \n", new_node);
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

            printf("priting rword by character: ");
            for(int i = 0; i < LENGTH+1; i++)
            {
                printf("%c", rword[i]);
            }
            printf("\n");

            new_node-> next = NULL;

            // find hashvalue from the hash function
            int hashval = hash(rword);

            // if hashed linked list is empty, the new node is the first node of the linked list;
            if (hashtable[hashval] == NULL)
            {
                hashtable[hashval] = new_node;
                printf("new_node [%s] inserted into hashval %i, new_node: %p\n.", new_node->word,hashval, hashtable[hashval]);
            }
            // else insert into a linked list
            else
            {
                new_node->next = hashtable[hashval];
                hashtable[hashval] = new_node;
            }
        }
    }

    // debug printf what's loaded in the hashtable
    for (int i = 0; i < 59; i++)
    {
        printf("hashtable: %i: ", i);
        if (hashtable[i]!=NULL)
        {
            node *ptr = hashtable[i];
            printf("There is a node here: %p", ptr);
            do
            {
                printf("words: %s, ",ptr->word);
                ptr = ptr->next;
            }
            while (hashtable[i]-> next != NULL);

        }
        printf("\n");
    }
    return true;
}


bool unload(void)
{
    for (int i = 0; i < 59; i++)
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





// testing check check
int main(void){
    hasht_init();
    load("dictionaries/small");
    bool x = check("CAT");
    printf("%s", x ? "true" : "false");
    x = check("Cat");
    printf("%s", x ? "true" : "false");
    unload();
}