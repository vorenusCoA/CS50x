// Implements a dictionary's functionality

#include <stdbool.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

int numberOfElements = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Case-insensitive
    int wordLength = strlen(word);
    char wordLower[wordLength + 1];
    for (int i = 0; i < wordLength + 1; i++)
    {
        wordLower[i] = tolower(word[i]);
    }

    // Now that we have a lowercase word we search
    int index = hash(wordLower);
    node *head = table[index];

    // Check if there is something at given index
    if (head != NULL)
    {
        if (strcmp(head->word, wordLower) == 0)
        {
            return true;
        }
        for (node *temp = head; temp->next != NULL; temp = temp->next)
        {
            if (strcmp(temp->word, wordLower) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

// Hashes word to a number
// djb2 by dan bernstein
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
     // Try to open the file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char tempWord[45 + 1];
    while (fscanf(dict, "%s", tempWord) != EOF)
    {
        // Count the chars before null
        int count = 0;
        for (int i = 0; i < 46; i++)
        {
            if (tempWord[i] != '\0')
            {
                count++;
            }
            else
            {
                break;
            }
        }
        // Create a word with the exacts characters
        char word[count + 1];
        for (int i = 0; i < count + 1; i++)
        {
            word[i] = tempWord[i];
        }
        int index = hash(word);
        node *head = table[index];
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            fclose(dict);
            return false;
        }

        strcpy(newNode->word, word);
        newNode->next = NULL;
        // If its empty then is the first element
        if (head == NULL)
        {
            table[index] = newNode;
        }
        else
        {
            // We insert it first
            newNode->next = head->next;
            table[index] = newNode;
        }
        // Increse the total number of elements in the table
        numberOfElements++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numberOfElements;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        if (cursor == NULL)
        {
            continue;
        }
        node *tmp = cursor;
        while(true)
        {
            if (cursor->next != NULL)
            {
                cursor = cursor->next;
                free (tmp);
                tmp = cursor;
            }
            else
            {
                free(cursor);
                break;
            }

        }
    }
    return true;
}
