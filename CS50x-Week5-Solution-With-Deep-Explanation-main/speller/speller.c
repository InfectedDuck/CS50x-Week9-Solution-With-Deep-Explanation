// Implements a spell-checker

#include <ctype.h>     // For character handling functions (isalpha, isdigit, etc.)
#include <stdio.h>     // For standard I/O functions (printf, fopen, fclose, etc.)
#include <sys/resource.h> // For resource usage functions (getrusage)
#include <sys/time.h>  // For time functions (struct timeval)

#include "dictionary.h" // Custom header file for dictionary functions

// Undefine any previous definitions for these macros
#undef calculate
#undef getrusage

// Default dictionary file path
#define DICTIONARY "dictionaries/large"

// Prototype for timing calculation function
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Check command-line arguments for correct usage
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    // Structures to store resource usage data for benchmarking
    struct rusage before, after;

    // Variables to hold timing benchmarks
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Determine which dictionary file to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Record the time before loading the dictionary
    getrusage(RUSAGE_SELF, &before);

    // Load the dictionary into memory
    bool loaded = load(dictionary);

    // Record the time after loading the dictionary
    getrusage(RUSAGE_SELF, &after);

    // Exit if dictionary could not be loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Calculate time taken to load the dictionary
    time_load = calculate(&before, &after);

    // Try to open the text file to be spell-checked
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();  // Unload dictionary before exiting
        return 1;
    }

    // Print header for misspelled words report
    printf("\nMISSPELLED WORDS\n\n");

    // Variables for tracking spell-check statistics
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];  // Buffer to hold each word

    // Read and process each character from the file
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        // Check if the character is part of a word (alphabetical or apostrophe)
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to the current word
            word[index] = c;
            index++;

            // Ignore strings that are too long to be valid words
            if (index > LENGTH)
            {
                // Consume the rest of the current word
                while (fread(&c, sizeof(char), 1, file) && isalpha(c));

                // Reset the index for the next word
                index = 0;
            }
        }
        // Ignore words containing numbers
        else if (isdigit(c))
        {
            // Consume the rest of the alphanumeric string
            while (fread(&c, sizeof(char), 1, file) && isalnum(c));

            // Reset the index for the next word
            index = 0;
        }
        // We have found a complete word
        else if (index > 0)
        {
            // Null-terminate the current word
            word[index] = '\0';

            // Increment the word counter
            words++;

            // Record time before checking the word's spelling
            getrusage(RUSAGE_SELF, &before);

            // Check if the word is misspelled
            bool misspelled = !check(word);

            // Record time after checking the word's spelling
            getrusage(RUSAGE_SELF, &after);

            // Update benchmark for spell-check time
            time_check += calculate(&before, &after);

            // Print the misspelled word
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Reset index for the next word
            index = 0;
        }
    }

    // Check if there was an error reading the file
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        unload();  // Unload dictionary before exiting
        return 1;
    }

    // Close the text file
    fclose(file);

    // Record time before determining dictionary size
    getrusage(RUSAGE_SELF, &before);

    // Determine the number of words in the dictionary
    unsigned int n = size();

    // Record time after determining dictionary size
    getrusage(RUSAGE_SELF, &after);

    // Calculate time taken to determine the dictionary's size
    time_size = calculate(&before, &after);

    // Record time before unloading the dictionary
    getrusage(RUSAGE_SELF, &before);

    // Unload the dictionary from memory
    bool unloaded = unload();

    // Record time after unloading the dictionary
    getrusage(RUSAGE_SELF, &after);

    // Abort if dictionary could not be unloaded
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Calculate time taken to unload the dictionary
    time_unload = calculate(&before, &after);

    // Report benchmarking results
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);

    // Return success code
    return 0;
}

// Returns number of seconds between times b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        // Calculate the elapsed time in seconds between two `rusage` structures
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
