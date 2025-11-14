from cs50 import get_string  # Import the get_string function from the cs50 module

# Initialize variables to accumulate sums for Luhn's algorithm
sum1, sum2, sum_temp = 0, 0, 0

# Prompt the user to enter a card number for validity check
card = get_string("Write the card you want to check for validity: ")

# Check if the input contains only digits
if not(card.isdigit()):
    print("INCORRECT")  # Print "INCORRECT" if the input is not a valid digit string
else:
    # Process each digit from right to left
    for i in range(len(card) - 1, -1, -1):
        digit = int(card[i])  # Convert the current digit character to an integer
        
        # If the position of the digit (counting from 1) is even, double the digit
        if (len(card) - i) % 2 == 0:
            double_digit = digit * 2
            # If doubling the digit results in a number greater than 9, add its digits
            if double_digit > 9:
                sum_temp += double_digit // 10 + double_digit % 10
            else:
                sum_temp += double_digit
            # Add the processed sum of the doubled digit to sum1
            sum1 += sum_temp
            sum_temp = 0  # Reset temporary sum for the next iteration
        else:
            # If the position is odd, simply add the digit to sum2
            sum2 += digit
    
    # Calculate the total sum for Luhn's algorithm
    sum3 = sum2 + sum1
    
    # Check if the total sum is a multiple of 10
    if (sum3 % 10 == 0):
        # Check the card type based on its length and starting digits
        if (len(card) == 13 or len(card) == 16) and card[0] == "4":
            print("VISA")  # Valid VISA card
        elif len(card) == 15 and card[0] == '3' and (card[1] == '4' or card[1] == '7'):
            print("AMEX")  # Valid American Express card
        elif len(card) == 16 and card[0] == '5' and ('1' <= card[1] <= '5'):
            print("MASTERCARD")  # Valid MasterCard
        else:
            print("INVALID")  # Card does not match known types
    else:
        print("INVALID")  # Total sum is not a multiple of 10, so the card is invalid
