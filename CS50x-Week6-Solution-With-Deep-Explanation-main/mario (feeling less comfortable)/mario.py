while True:
    try:
        # Prompt the user to enter the height of the pyramid
        height = int(input("Height: "))
        # Check if the entered height is within the valid range (1 to 8 inclusive)
        if 1 <= height <= 8:
            break  # Exit the loop if the height is valid
        else:
            # Inform the user that the input is invalid if it's not in the range
            print("Invalid input. Please enter a number between 1 and 8.")
    except ValueError:
        # Handle the case where the user input is not a valid integer
        print("Invalid input. Please enter a valid integer.")

# Generate the pyramid
for i in range(1, height + 1):
    # Construct and print each row of the pyramid
    # ' ' * (height - i) calculates the number of leading spaces needed for the current row
    # '#' * i creates the number of hashes needed for the current row
    # Print the row by concatenating spaces and hashes
    print(' ' * (height - i) + '#' * i)
