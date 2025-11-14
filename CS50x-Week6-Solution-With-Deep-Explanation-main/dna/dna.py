import csv  # Import the CSV module to handle reading from and writing to CSV files
import sys  # Import the sys module to access command-line arguments

def main():
    # Check if the script is run with exactly two command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py csvfile sequencetxtfile")
        return  # Exit the program if the number of arguments is incorrect

    # Assign command-line arguments to variables
    csvfile = sys.argv[1]  # The first argument is the path to the CSV file containing DNA profiles
    txtfile = sys.argv[2]  # The second argument is the path to the text file containing the DNA sequence

    # Initialize empty lists to store data
    person_DNA_sequences = []  # List to store the DNA profiles from the CSV file
    DNA_sequences = []  # List to store the names of the STRs from the CSV file
    longest_matches = []  # List to store the longest runs of each STR found in the DNA sequence

    # Read the CSV file containing DNA profiles
    with open(csvfile, mode='r', newline='') as file_csv:
        reader = csv.reader(file_csv)  # Create a CSV reader object to read the file
        DNA_sequences = next(reader)  # Read the first row which contains STR names
        for row in reader:
            person_DNA_sequences.append(row)  # Append each subsequent row to the list of DNA profiles

    # Remove the first item from the DNA_sequences list, which is a header
    DNA_sequences = DNA_sequences[1:]

    # Read the DNA sequence from the text file
    with open(txtfile, mode='r') as file_txt:
        sequence = file_txt.read().strip()  # Read the content of the file and remove any leading/trailing whitespace

    # Find the longest run of each STR in the DNA sequence
    for subsequence in DNA_sequences:
        longest_matches.append(longest_match(sequence, subsequence))  # Append the result of the longest_match function for each STR

    match_found = False  # Initialize a flag to indicate whether a matching profile is found

    # Check each profile in the database for a match
    for j in range(len(person_DNA_sequences)):
        count = 0  # Counter for matching STRs
        # Compare the longest match counts with the STR counts in the profile
        for i in range(1, len(person_DNA_sequences[j])):
            if int(person_DNA_sequences[j][i]) == longest_matches[i-1]:
                count += 1  # Increment the count if there's a match

        # If all STRs in the profile match the longest matches found in the DNA sequence
        if count == len(person_DNA_sequences[j]) - 1:
            print(person_DNA_sequences[j][0])  # Print the name of the matching profile
            match_found = True  # Set the flag to True indicating a match was found

    # If no matching profile was found, print "No match"
    if not match_found:
        print("No match")

def longest_match(sequence, subsequence):
    """Returns the length of the longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0  # Tracks the length of the longest run of the subsequence found
    subsequence_length = len(subsequence)  # Length of the subsequence to match
    sequence_length = len(sequence)  # Length of the DNA sequence

    # Check each position in the sequence for the longest run of subsequence
    for i in range(sequence_length):
        count = 0  # Initialize count of consecutive runs of subsequence

        # Continuously check for matches of the subsequence starting from position i
        while True:
            start = i + count * subsequence_length  # Calculate the start index of the substring to check
            end = start + subsequence_length  # Calculate the end index of the substring to check

            # If the substring matches the subsequence
            if sequence[start:end] == subsequence:
                count += 1  # Increment the count of consecutive matches
            else:
                break  # Exit the loop if the substring does not match

        # Update the longest run found if the current count is greater
        longest_run = max(longest_run, count)

    # Return the length of the longest run of subsequence found in the sequence
    return longest_run

# Call the main function to execute the program
main()
