// Implements a dictionary's functionality
// Hash function from https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c

#include <stdbool.h>
#include "dictionary.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
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
int total_words = 0;

// Hash table
node *table[N];

bool delete (node *n);

// Function to recursively search through a linked list for a word
bool search(node *n, const char *word)
{

    if (n == NULL)
    {
        return false;
    }
    
    if (strcasecmp(n -> word, word) == 0)
    {
        return true;
    }
    else
    {
        return search(n -> next, word);
    }

}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain value
    int value = hash(word);
 
    // Access linked list in that hash table index
    char *check_buckets = table[value] -> word;

    // If this bucket doesn't have entries, it's not there
    if (check_buckets  == NULL)
    {
        return false;

    }
    else
    {
        // If the search function found the word, return true
        int result = search(table[value], word);
        if (result == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// Hashes word to a number
// Hash function from https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
unsigned int hash(const char *word)
{
    // Copy the word in new string
    char lowercase_word[strlen(word)];
    strcpy(lowercase_word, word);

    // Make the string lowercase
    for (int i = 0; i < strlen(word); i++)
    {
        lowercase_word[i] = tolower(lowercase_word[i]);
    }
    
    // Calculate hash value
    unsigned hash_value;
    for (hash_value = 0; *word != '\0'; word++)
    {
        hash_value = *lowercase_word + 31 * hash_value;
    }
      
    return hash_value % N;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary and return false if that fails
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    else
    {

        char entry[LENGTH];
        // Keep scanning the file for words until EOF is reached
        while (fscanf(dict, "%s", entry) == 1)
        {
            // Update global variable of total words
            total_words ++;
            node *words = NULL;
            node *n = malloc(sizeof(node));

            if (n == NULL)
            {
                free(words);
                return false;
            }

            else
            {
                unsigned int val = hash(entry);
                char *check_buckets = table[val] -> word;

                // If this bucket doesn't have entries yet
                if (check_buckets == NULL)
                {
                    strcpy(n -> word, entry);
                    n -> next = NULL;
                    table[val] = n;
                }
                // Else insert in front of the already existing list
                else
                {
                    strcpy(n -> word, entry);
                    n -> next = table[val];
                    table[val] = n;
                }
            }
        }
        //print_dict(table[90]);
        fclose(dict);
        return true;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the global variable of total words, if it's 0 then it hasn't been loaded yet
    if (total_words > 0)
    {
        return total_words;
    }
    else
    {
        return 0;
    }

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Call the delete function for each index in the hash table to delete each linked list
    int index = 0;
    int i = 0;
    for (i = 0; i < N; i++)
    {
        delete (table[i]);

    }
    free(table[i]);
    return true;
}

bool delete (node *n)
{
    // Recursively delete each entry in the linked list
    if (n == NULL)
    {
        return true;
    }

    node *tmp = n;
    n = n -> next;
    free(tmp);
    delete (n);

    return false;

}
