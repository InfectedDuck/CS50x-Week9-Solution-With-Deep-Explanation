#include <cs50.h>    // Include the CS50 library for getting input from the user
#include <stdio.h>    // Include the standard input/output library for printing output
#include <stdlib.h>   // Include the standard library for conversion functions
#include <ctype.h>    // Include the ctype library for character type functions

int main(int argc, string argv[])
{
    // Check if the number of command-line arguments is exactly 2 (program name and key)
    if (argc != 2)
    {
        // Print usage message if the number of arguments is incorrect
        printf("Usage: %s key\n", argv[0]); // argv[0] is the program name
        return 1; // Exit with status 1 to indicate an error
    }

    // Iterate over each character in the key argument to check if it is a digit
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        // Check if the current character is not a digit
        if (!isdigit(argv[1][i]))
        {
            // Print an error message if the key contains non-digit characters
            printf("Key must be a non-negative integer.\n");
            return 1; // Exit with status 1 to indicate an error
        }
    }

    // Convert the key from a string to an integer
    int k = atoi(argv[1]); // atoi converts a string to an integer

    // Prompt the user to enter plaintext
    string p = get_string("plaintext: ");

    // Print the header for the ciphertext
    printf("ciphertext: ");

    // Iterate over each character in the plaintext
    for (int i = 0; p[i] != '\0'; i++)
    {
        // Store the current character
        char c = p[i];

        // Check if the character is an alphabetic letter
        if (isalpha(c))
        {
            // Determine the base character ('A' for uppercase letters, 'a' for lowercase letters)
            char base = isupper(c) ? 'A' : 'a';
            // Encrypt the character using the Caesar cipher formula
            c = (c - base + k) % 26 + base;
        }

        // Print the (possibly encrypted) character
        printf("%c", c);
    }

    // Print a newline character to finish the ciphertext output
    printf("\n");

    return 0; // Return 0 to indicate successful completion of the program
}
