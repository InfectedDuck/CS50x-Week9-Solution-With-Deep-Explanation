// Implements a dictionary's functionality

#include <ctype.h>      // For character handling functions (tolower)
#include <stdbool.h>    // For boolean type (bool)
#include <string.h>     // For string manipulation functions (strcpy, strcasecmp)
#include <stdlib.h>     // For memory allocation functions (malloc, free)
#include <stdio.h>      // For standard I/O functions (fopen, fscanf, fclose)
#include <strings.h>   // For case-insensitive string comparison (strcasecmp)

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];  // Word stored in the node
    struct node *next;      // Pointer to the next node in the list
} node;

// Number of buckets in the hash table (hash table size)
const unsigned int N = 65366;

// Hash table
node *table[N];  // Array of pointers to nodes
int number_of_words = 0; // Number of words in the dictionary

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to find the appropriate bucket
    int word_ind = hash(word);

    // Traverse the linked list at the hashed index
    node *cursor = table[word_ind];
    while (cursor != NULL)
    {
        // Compare the word with the current node's word (case-insensitive)
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;  // Word found
        }
        cursor = cursor->next;  // Move to the next node
    }
    return false;  // Word not found
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_val = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Convert character to lowercase
        char lowercase_char = tolower(word[i]);

        // Hash function: shift hash_val and add character's ASCII value
        hash_val = hash_val * 31 + lowercase_char;
    }
    return hash_val % N;  // Return index within hash table size
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file for reading
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Couldn't open dictionary\n");
        return false;
    }

    char word[LENGTH + 1];
    // Read each word from the file
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Allocate memory for a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(dict);
            printf("Memory allocation failed\n");
            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);

        // Hash the word to find the appropriate index
        unsigned int ind = hash(word);

        // Insert the new node into the hash table
        new_node->next = table[ind];
        table[ind] = new_node;

        // Increment the word count
        number_of_words += 1;
    }
    fclose(dict);  // Close the dictionary file
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the number of words in the dictionary
    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        // Traverse the linked list and free each node
        while (cursor != NULL)
        {
            node *tmp = cursor;  // Store pointer to current node
            cursor = cursor->next;  // Move to the next node
            free(tmp);  // Free memory of the current node
        }
    }
    return true;
}
