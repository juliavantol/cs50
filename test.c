// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 101;

// Hash table
node *table[N];

// Implement load. CHECK
// Implement hash.
// Implement size.
// Implement check.
// Implement unload.

void print_dict(node *n);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned hashval;
    for (hashval = 0; *word != '\0'; word++)
      hashval = *word + 31 * hashval;
    return hashval % N;

}
// https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    else
    {

        node *words = NULL;


        int index = 0;
        char entry[LENGTH];


        // Keep scanning the file for words until EOF is reached
        while(fscanf(dict, "%s", entry) == 1)
        {

            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                free(words);
                return false;
            }

            else
            {
                
                unsigned int val = hash(entry);
                printf("Hash value: %i\n", val);
                strcpy(n -> word, entry);

                

                // if this is the first word of the list, set it to head of list
                if (index == 0)
                {
                    
                    n -> next = NULL;
                    words = n;
                    table[val] = words;

                }

                // insert this node in one of the linked lists in hash table based on result of hash function

                else
                {
                    // Put new node in front of last one
                    n -> next = words;
                    words = n;
                    table[val] = words;



                }

                index++;

            }


        }
        // how to get first word = words[0].word
        // how to get next word = words[0].next->word
        print_dict(words);
        // printf("Word: %s\n", words ->word);
        // printf("Next: %s\n", words ->next->word);
        // printf("\n");
        // printf("Word: %s\n", words ->next->word);
        // printf("Next: %s\n", words ->next->next->word);

      

        return true;

    }
    return false;
}

// Print each family member and their alleles.
void print_dict(node *n)
{
    // Handle base case
    if (n == NULL)
    {
        return;
    }

   
    // Print person
    printf("Word: %s\nNext: %s\n", n -> word, n->next->word);
    print_dict(n -> next);

}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}


     // char c = fgetc(dict);
        // int index = 0;

        // while (c != EOF)
        // {

        //     node *n = malloc(sizeof(node));

        //     strcpy(n->word, &c);
        //     n->next = NULL;

        //     table[index] = n;

        //     c = fgetc(dict);
        //     index++;

        // }

        // fclose(dict);
