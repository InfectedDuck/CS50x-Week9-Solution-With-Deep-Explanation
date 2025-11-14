#include <cs50.h>      // Include the CS50 library for getting input from the user
#include <ctype.h>     // Include the ctype library for character type functions
#include <stdio.h>     // Include the standard input/output library
#include <string.h>    // Include the string library for string manipulation functions
#include <stdlib.h>    // Include the standard library for general purpose functions

int main(void)
{
    // Variable to store the credit card number input by the user
    long card;
    // Variables to store the sums used in the Luhn algorithm
    int sum1 = 0;       // Sum of digits obtained from multiplying every other digit by 2
    int sum2 = 0;       // Sum of digits that were not multiplied by 2
    int sum3 = 0;       // Total sum of sum1 and sum2
    int temp = 0;       // Temporary variable to hold the product of a digit multiplied by 2
    int sum_temp = 0;   // Temporary variable to sum the individual digits of the product if it has two digits
    // Strings to temporarily store numbers during calculations
    char sum3_str[15];  // String to hold the final sum (not actually used in the code)
    char temp_str[15];  // String to hold the product of a digit multiplied by 2
    char str[21];       // String to hold the card number as a string

    // Infinite loop to continually prompt the user for a valid card number
    while (1)
    {
        // Prompt the user to enter the credit card number and store it in the variable 'card'
        card = get_long("Write the card you want to check for validity: ");
        // Convert the card number from a long integer to a string and store it in 'str'
        sprintf(str, "%ld", card);
        int i = 0;          // Initialize an index for iterating over the string
        int isValid = 1;    // Variable to track if the input is valid (1 for valid, 0 for invalid)

        // Loop to check if the entered string consists only of digits
        while (str[i] != '\0')  // Loop until the end of the string
        {
            // Check if the current character is not a digit
            if (!isdigit((unsigned char)str[i]))
            {
                isValid = 0;    // Set isValid to 0 (false) if a non-digit character is found
                break;          // Exit the loop as the input is invalid
            }
            i++;                // Move to the next character in the string
        }

        // If the input is valid (contains only digits), proceed with the Luhn algorithm
        if (isValid)
        {
            // Iterate over the string from the end to the beginning
            for (int b = strlen(str) - 1; b >= 0; b--)
            {
                // Check if the position (counting from the end) is even
                if ((strlen(str) - b) % 2 == 0)
                {
                    // Convert the current character to an integer
                    int temp_int = str[b] - '0';
                    // Multiply the digit by 2
                    temp = temp_int * 2;
                    // Convert the product to a string to check its length
                    sprintf(temp_str, "%i", temp);

                    // If the product has two digits, add the individual digits to sum1
                    if (strlen(temp_str) >= 2)
                    {
                        // Iterate over the characters of the product string
                        for (int j = 0; j < strlen(temp_str); j++)
                        {
                            // Add the individual digits to sum_temp
                            sum_temp += temp_str[j] - '0';
                        }
                        // Add sum_temp to sum1 and reset sum_temp
                        sum1 += sum_temp;
                        sum_temp = 0;
                    }
                    // If the product has one digit, add it directly to sum1
                    else
                    {
                        sum1 += temp;
                    }
                }
                // If the position (counting from the end) is odd, add the digit to sum2
                else
                {
                    int temp_int = str[b] - '0';  // Convert the current character to an integer
                    sum2 += temp_int;             // Add the digit to sum2
                }
            }

            // Calculate the total sum of sum1 and sum2
            sum3 = sum2 + sum1;
            // Check if the total sum is divisible by 10 (Luhn's algorithm check)
            if (sum3 % 10 == 0)
            {
                // Check for VISA card: length is 13 or 16 and starts with '4'
                if ((strlen(str) == 13 || strlen(str) == 16) && str[0] == '4')
                {
                    printf("VISA\n");   // Print VISA if the conditions match
                }
                // Check for AMEX card: length is 15 and starts with '34' or '37'
                else if (strlen(str) == 15 && str[0] == '3' && (str[1] == '4' || str[1] == '7'))
                {
                    printf("AMEX\n");   // Print AMEX if the conditions match
                }
                // Check for MASTERCARD: length is 16 and starts with '51' to '55'
                else if (strlen(str) == 16 && str[0] == '5' && (str[1] >= '1' && str[1] <= '5'))
                {
                    printf("MASTERCARD\n");   // Print MASTERCARD if the conditions match
                }
                // If none of the conditions match, print INVALID
                else
                {
                    printf("INVALID\n");  // Print INVALID if no card type matches
                }
            }
            // If the total sum is not divisible by 10, the card is invalid
            else
            {
                printf("INVALID\n");  // Print INVALID if the Luhn check fails
            }
            break;  // Exit the infinite loop as a valid or invalid result has been determined
        }
    }
    return 0;  // Return 0 to indicate successful completion of the program
}
