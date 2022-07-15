// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int h = hash(word);

    node *p;
    p = table[h];

    char word1[LENGTH + 1];
    strcpy(word1, word);

    for (int i = 0; i < strlen(word1); i++)
    word1[i] = tolower(word1[i]);

    while (p != NULL)
    {
        // Copy and make case insensitive

        char word2[LENGTH + 1];
        strcpy(word2, p->word);

        for (int i = 0; i < strlen(word2); i++)
            word2[i] = tolower(word2[i]);

        // Compare
        if (strcmp(word1, word2) == 0)
        {
            return true;
        }
        p = p->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function

    int first = word[0];

    if (first >= (int)'A' && first <= (int)'Z')
        first -= (int)'A';
    else if (first >= (int)'a' && first <= (int)'z')
        first -= (int)'a';

    return first;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
        return false;

    char w[LENGTH + 1];
    while (fscanf(f, "%s", w) != EOF)
    {
        node *p = malloc(sizeof(node));
        unsigned int h = hash(w);
        if (table[h] != NULL)
        {
            p->next = table[h];
        }
        strcpy(p->word, w);
        table[h] = p;
        p = NULL;
    }

    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int res = 0;
    node *p;
    for (int i = 0; i < N; i++)
    {
        p = table[i];
        while (p != NULL)
        {
            res++;
            p = p->next;
        }
    }
    return res;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp;
    node *p;
    for (int i = 0; i < N; i++)
    {
        p = table[i];
        while (p != NULL)
        {
            tmp = p;
            p = p->next;
            free(tmp);
        }
        free(p);
    }
    return true;
}
