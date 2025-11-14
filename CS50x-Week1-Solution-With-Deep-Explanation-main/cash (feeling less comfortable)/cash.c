#include <cs50.h> // This library is used to leverage the get_int function, which helps in safely getting integer input from the user.
#include <stdio.h> // This library is used for input and output functions like printf.

int main(void) // function is the entry point of the program.
{
    // Variable to store the amount of money (in cents) that the user owes as change.
    int money;
    
    // Prompt the user to enter a non-negative amount of change owed.
    // This loop continues until a non-negative integer is entered.
    do
    {
        // Get the change owed from the user.
        money = get_int("Change owed: ");
    } while (money < 0); // Repeat the loop if the entered value is negative.

    // Calculate the number of quarters (25 cents each).
    int quarters = money / 25;
    // Update the remaining amount of money after using quarters.
    money %= 25;

    // Calculate the number of dimes (10 cents each).
    int dimes = money / 10;
    // Update the remaining amount of money after using dimes.
    money %= 10;

    // Calculate the number of nickels (5 cents each).
    int nickels = money / 5;
    // Update the remaining amount of money after using nickels.
    money %= 5;

    // The remaining money is entirely in pennies (1 cent each).
    int pennies = money;
    
    // Calculate the total number of coins used.
    int total_coins = quarters + dimes + nickels + pennies;
    
    // Print the total number of coins required to make the change.
    printf("%d\n", total_coins);
}
