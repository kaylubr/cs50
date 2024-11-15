// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5501;

// Hash table
node *table[N];

// Counter for size function
int size_counter = 0;

void initialize_table(void)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
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
    int sum = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        sum += tolower(word[i]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *book = fopen(dictionary, "r");
    if (!book)
    {
        return false;
    }

    initialize_table();

    char buffer[LENGTH + 1];

    while (fscanf(book, "%s", buffer) != EOF)
    {
        node *word_node = malloc(sizeof(node));
        if (!word_node)
        {
            return false;
        }

        strcpy(word_node->word, buffer);
        word_node->next = NULL;

        int index = hash(word_node->word);

        if (table[index] == NULL)
        {
            table[index] = word_node;
        }

        else
        {
            word_node->next = table[index];
            table[index] = word_node;
        }

        size_counter++;
    }

    fclose(book);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while (tmp != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }

        table[i] = NULL;
    }

    return true;
}
