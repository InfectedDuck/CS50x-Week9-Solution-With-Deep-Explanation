# Import the get_float function from the cs50 library
from cs50 import get_float

# Continuously prompt the user for input until a valid non-negative value is provided
while True:
    # Use get_float to prompt the user for the amount of change owed
    # This function displays the prompt message and waits for the user to enter a floating-point number
    change = get_float("Change owed: ")
    
    # Check if the provided amount of change is non-negative
    if change >= 0:
        # Exit the loop if a valid (non-negative) input is received
        break
    else:
        # If the input is negative, print an error message and prompt the user again
        print("Invalid input. Please enter a non-negative value.")

# Convert the amount of change from dollars to cents
# This is done to handle the change in integer values (cents) for easier coin calculations
# Multiply by 100 and round to the nearest whole number to avoid floating-point precision issues
cents = round(change * 100)

# Define the values of the different coin denominations in cents
quarters = 25  # Value of one quarter in cents
dimes = 10     # Value of one dime in cents
nickels = 5    # Value of one nickel in cents
pennies = 1    # Value of one penny in cents

# Initialize a counter to keep track of the total number of coins used
num_coins = 0

# Calculate the number of quarters needed
# Use integer division to determine how many quarters fit into the total cents
num_coins += cents // quarters
# Update the remaining cents after accounting for quarters
cents %= quarters

# Calculate the number of dimes needed
# Use integer division to determine how many dimes fit into the remaining cents
num_coins += cents // dimes
# Update the remaining cents after accounting for dimes
cents %= dimes

# Calculate the number of nickels needed
# Use integer division to determine how many nickels fit into the remaining cents
num_coins += cents // nickels
# Update the remaining cents after accounting for nickels
cents %= nickels

# Calculate the number of pennies needed
# Use integer division to determine how many pennies fit into the remaining cents
num_coins += cents // pennies

# Output the total number of coins needed to make the change
print(num_coins)
