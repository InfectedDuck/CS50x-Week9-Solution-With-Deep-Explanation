#include <cs50.h>  // Include the CS50 library for getting input from the user
#include <stdio.h> // Include the standard input/output library for printing output

int main(void)
{
    // Prompt the user to enter their name and store it in the variable 'name'
    string name = get_string("What's your name? ");
    
    // Print a greeting message that includes the user's name
    printf("Hello, %s\n", name);
    
    // Return 0 to indicate successful completion of the program
    return 0;
}
