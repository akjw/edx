// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// alternate N
// const unsigned int N = LENGTH * 'z' ;


//init sum of words
int sum = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)];

    // hash word to get hash value
    // index into hash table at hash value
    // traverse linked list to look for word (strcmp)
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int index = tolower(word[0]) - 'a';
    return index;
}

// alternate hash function --- add ascii values of all letters
// unsigned int hash(const char *word)
// {
//     int sum = 0;
//     for (int i = 0; i < strlen(word); i++)
//     {
//         sum += tolower(word[i]);
//     }
//     return (sum % N);
// }


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // Open file (use fopen; check if return is NULL-->return false)
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char currentWord[LENGTH + 1];
    // for (int i = 0; i < N; i++)
    // {
    //     table[i] = NULL;
    // }
    // Read strings from dict one by one (fscanf(file (pointer), "%s", word(character array inside memory)); will return EOF at the end)
    while(fscanf(file, "%s", currentWord) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // Create node for each word (malloc, check if return value is null, copy word into node using strcpy)
        strcpy(n->word, currentWord);
        // Hash word to obtain value (use hash func; this will return an index)
        // Insert node into hash table at given location ()
        // if (table[hash(currentWord)] == NULL)
        // {
        //     n->next = NULL;
        //     table[hash(currentWord)] = n;
        // }
        // else
        // {
        //     n->next = table[hash(currentWord)];
        // Point head to new node at beginning of the list
        //     table[hash(currentWord)] = n;
        // }
        n->next = table[hash(currentWord)];
        // Point head to new node at beginning of the list
        table[hash(currentWord)] = n;
        sum++;
    }
    // close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return sum;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        free(cursor);
    }
    return true;
}
