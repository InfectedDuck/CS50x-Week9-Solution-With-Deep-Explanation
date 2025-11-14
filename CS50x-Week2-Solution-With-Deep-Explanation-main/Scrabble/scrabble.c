#include <cs50.h>    // Include the CS50 library for getting input from the user
#include <stdio.h>   // Include the standard input/output library for printing output
#include <stdlib.h>  // Include the standard library for functions like malloc and free (not used in this code but often included)
#include <string.h>  // Include the string library for string manipulation functions
#include <ctype.h>   // Include the ctype library for character type functions (e.g., isalpha, tolower)

// Array defining the points for each letter in the alphabet
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Function prototype for calculating the score of a given word
int scores(const char *word);

int main(void)
{
    // Get the words from two players
    string word1 = get_string("Player1: "); // Input for Player 1
    string word2 = get_string("Player2: "); // Input for Player 2

    // Calculate the scores for both players
    int score1 = scores(word1); // Score for Player 1
    int score2 = scores(word2); // Score for Player 2

    // Compare the scores and print the result
    if (score1 == score2)
    {
        printf("Tie!\n"); // Print if the scores are equal
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins!\n"); // Print if Player 1 has a higher score
    }
    else
    {
        printf("Player 2 wins!\n"); // Print if Player 2 has a higher score
    }

    return 0; // Return 0 to indicate successful completion of the program
}

// Function to calculate the score of a given word based on letter values
int scores(const char *word)
{
    int score = 0; // Initialize score to 0

    // Iterate over each character in the word
    for (int i = 0; i < strlen(word); i++)
    {
        // Check if the current character is an alphabetic letter
        if (isalpha(word[i]))
        {
            // Convert the letter to lowercase and calculate its index (0 for 'a', 1 for 'b', etc.)
            score += points[tolower(word[i]) - 'a']; // Add the corresponding points to the score
        }
    }

    return score; // Return the calculated score
}
