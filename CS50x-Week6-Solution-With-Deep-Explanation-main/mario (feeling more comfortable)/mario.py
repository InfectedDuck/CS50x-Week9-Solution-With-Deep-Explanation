from cs50 import get_int  # Import the get_int function from the cs50 module for integer input

height = 0  # Initialize height to 0 (or any value outside the valid range)

# Continuously prompt the user to enter a valid height (between 1 and 8 inclusive)
while height < 1 or height > 8:
    height = get_int("Height: ")  # Read an integer input from the user and store it in 'height'

# Generate and print the pyramid
for i in range(1, height + 1):
    # Construct and print each row of the pyramid
    # ' ' * (height - i) calculates the number of leading spaces needed for the left-aligned portion
    # '#' * i creates the number of hashes needed for the left-aligned portion of the pyramid
    # '  ' adds two spaces between the two pyramid halves
    # '#' * i creates the number of hashes needed for the right-aligned portion of the pyramid
    # 'sep=""' prevents adding extra spaces between the concatenated strings
    print(" " * (height - i) + "#" * i + "  " + "#" * i, sep="")
