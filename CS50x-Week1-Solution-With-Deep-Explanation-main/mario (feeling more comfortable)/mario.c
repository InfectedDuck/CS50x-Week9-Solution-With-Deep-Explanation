#include <stdio.h> // Include the standard input/output library for printing output
#include <cs50.h> // Include the CS50 library for getting input from the user

int main(void)
{
    int height; // Variable to store the height of the object (pyramid)

    // Prompt the user to enter a height between 1 and 8 (inclusive)
    do
    {
        height = get_int("Write the height of an object: "); // Get the height from the user
    }
    while (height < 1 || height > 8); // Repeat the prompt if the height is not within the valid range

    // Loop to construct each row of the pyramid
    for (int i = 1; i <= height; i++)
    {
        // Print spaces before the hashes for the left side of the pyramid
        for (int j = 0; j < height - i; j++)
        {
            printf(" "); // Print a space
        }

        // Print hashes for the left side of the pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#"); // Print a hash
        }

        // Print two spaces between the two sides of the pyramid
        printf("  "); // Print two spaces

        // Print hashes for the right side of the pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#"); // Print a hash
        }

        // Move to the next line after completing the current row
        printf("\n");
    }

    return 0; // Return 0 to indicate successful completion of the program
}
