#include <cs50.h>    // Include the CS50 library for getting input from the user
#include <stdio.h>   // Include the standard input/output library for printing output
#include <ctype.h>   // Include the ctype library for character type functions (e.g., isalpha, tolower)
#include <string.h>  // Include the string library for string manipulation functions (e.g., strlen, strcat)
#include <stdlib.h>  // Include the standard library for functions like malloc and free (not used in this code but often included)

// Main function that handles the encryption process
int main(int argc, string argv[])
{
    string key = argv[1]; // Get the key from the command-line argument
    char cipher[100] = ""; // Initialize an empty string to store the ciphertext
    int letter_count[26] = {0}; // Array to track occurrences of each letter in the key

    // Check if the number of command-line arguments is exactly 2 (program name and key)
    if (argc != 2)
    {
        // Print usage message if the number of arguments is incorrect
        printf("Usage: %s <key>\n", argv[0]); // argv[0] is the program name
        return 1; // Exit with status 1 to indicate an error
    }
    // Check if the length of the key is exactly 26 characters
    else if (strlen(key) != 26)
    {
        // Print an error message if the key length is incorrect
        printf("Key must contain 26 characters.\n");
        return 1; // Exit with status 1 to indicate an error
    }
    else
    {
        // Validate the key for non-alphabetic characters and duplicates
        for (int i = 0; i < 26; i++)
        {
            // Check if the character at the current index is not alphabetic
            if (isalpha(key[i]) == 0)
            {
                // Print an error message if the key contains non-alphabetic characters
                printf("INVALID! Non-alphabetic character in key.\n");
                return 1; // Exit with status 1 to indicate an error
            }
            int index = tolower(key[i]) - 'a'; // Convert the key character to lowercase and calculate its index
            // Check if the letter has already been encountered (i.e., it's a duplicate)
            if (letter_count[index] > 0)
            {
                // Print an error message if the key contains duplicate characters
                printf("Duplicate in key!\n");
                return 1; // Exit with status 1 to indicate an error
            }
            letter_count[index]++; // Mark the letter as encountered
        }

        // Get the plaintext input from the user
        string plaintext = get_string("plaintext: ");

        // Encrypt the plaintext using the key
        for (int j = 0; j < strlen(plaintext); j++)
        {
            // Check if the current character is a lowercase letter
            if (islower(plaintext[j]))
            {
                int index = plaintext[j] - 'a'; // Calculate the index for the key
                char cipher1[2] = {tolower(key[index]), '\0'}; // Get the corresponding cipher character
                strcat(cipher, cipher1); // Append the cipher character to the ciphertext
            }
            // Check if the current character is an uppercase letter
            else if (isupper(plaintext[j]))
            {
                int index = plaintext[j] - 'A'; // Calculate the index for the key
                char cipher2[2] = {toupper(key[index]), '\0'}; // Get the corresponding cipher character
                strcat(cipher, cipher2); // Append the cipher character to the ciphertext
            }
            else
            {
                char cipher3[2] = {plaintext[j], '\0'}; // For non-alphabetic characters, use them as-is
                strcat(cipher, cipher3); // Append the character to the ciphertext
            }
        }

        // Print the resulting ciphertext
        printf("ciphertext: %s\n", cipher);

        return 0; // Return 0 to indicate successful completion of the program
    }
}
