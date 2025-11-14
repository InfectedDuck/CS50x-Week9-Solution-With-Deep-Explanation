#include <ctype.h>   // Include the ctype library for character type functions (e.g., isalpha)
#include <cs50.h>    // Include the CS50 library for getting input from the user
#include <math.h>    // Include the math library for mathematical functions (e.g., round)
#include <stdio.h>   // Include the standard input/output library for printing output
#include <string.h>  // Include the string library for string manipulation functions

int main(void)
{
    // Initialize counters for letters, sentences, and words
    int letters_count = 0;    // Count of alphabetic letters in the text
    int sentences_count = 0;  // Count of sentence-ending punctuation marks
    int words_count = 1;      // Count of words in the text (starts at 1 for the first word)

    // Get the text input from the user
    string text = get_string("Write the text you want to check for grade: ");

    // Iterate over each character in the text
    for (int i = 0; i < strlen(text); i++)
    {
        // Check if the current character is an alphabetic letter
        if (isalpha(text[i]))
        {
            letters_count++;  // Increment the letter count
        }
        // Check if the current character is a space
        else if (text[i] == ' ')
        {
            words_count++;  // Increment the word count
        }
        // Check if the current character is a sentence-ending punctuation mark
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences_count++;  // Increment the sentence count
        }
    }

    // Calculate the average number of letters per 100 words
    double L = ((double) letters_count / words_count) * 100.0;
    // Calculate the average number of sentences per 100 words
    double S = ((double) sentences_count / words_count) * 100.0;
    // Compute the Coleman-Liau index using the formula
    int index = (int) round(0.0588 * L - 0.296 * S - 15.8);

    // Determine the grade based on the index value
    if (index > 16)
    {
        printf("Grade 16+\n");  // If the index is greater than 16, print "Grade 16+"
    }
    else if (index <= 1)
    {
        printf("Before Grade 1\n");  // If the index is 1 or less, print "Before Grade 1"
    }
    else
    {
        printf("Grade %i\n", index);  // Print the grade corresponding to the index value
    }

    return 0;  // Return 0 to indicate successful completion of the program
}
