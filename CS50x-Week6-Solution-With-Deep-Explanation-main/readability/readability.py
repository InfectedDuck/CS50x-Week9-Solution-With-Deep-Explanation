from cs50 import get_string  # Import the get_string function from the cs50 module for string input

# Initialize counters for letters, sentences, and words
letters = 0
sentences = 0
words = 1  # Start words at 1 to account for the first word before any spaces

# Prompt the user to enter a string of text
text = get_string("Text: ")

# Iterate over each character in the input text
for i in range(len(text)):
    # Check if the character is a letter
    if text[i].isalpha():
        letters += 1  # Increment the letter count
    # Check if the character is a space
    elif text[i] == ' ':
        words += 1  # Increment the word count
    # Check if the character is a sentence-ending punctuation
    elif text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentences += 1  # Increment the sentence count

# Calculate the average number of letters per 100 words
Li = (letters / words) * 100

# Calculate the average number of sentences per 100 words
Si = (sentences / words) * 100

# Compute the Coleman-Liau index based on the formula
index = round(0.0588 * Li - 0.296 * Si - 15.8)

# Determine and print the grade level based on the index
if index > 16:
    print("Grade 16+")  # If the index is greater than 16, print "Grade 16+"
elif index <= 1:
    print("Before Grade 1")  # If the index is 1 or less, print "Before Grade 1"
else:
    print("Grade", index)  # For other values, print the corresponding grade level
