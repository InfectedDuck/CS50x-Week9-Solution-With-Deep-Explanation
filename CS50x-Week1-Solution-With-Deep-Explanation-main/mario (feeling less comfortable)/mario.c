#include <cs50.h> // Include the CS50 library for getting input from the user
#include <stdio.h> // Include the standard input/output library for printing output

int main(void)
{
    int size; // Variable to store the height of the pyramid

    // Prompt the user to enter a height between 1 and 8 (inclusive)
    do {
        size = get_int("Height: "); // Get the height from the user
    } while (size < 1 || size > 8); // Repeat the prompt if the height is not within the valid range

    // Loop to construct each row of the pyramid
    for (int i = 0; i < size; i++)
    {
        // Print spaces before the hashes to align the pyramid to the right
        for (int j = 0; j < size - i - 1; j++)
        {
            printf(" "); // Print a space
        }

        // Print hashes for the current row
        for (int k = 0; k <= i; k++)
        {
            printf("#"); // Print a hash
        }

        // Move to the next line after completing the current row
        printf("\n");
    }

    return 0; // Return 0 to indicate successful completion of the program
}
