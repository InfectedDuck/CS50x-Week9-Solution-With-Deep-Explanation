# CS50 Programs Documentation

### ⭐️ **Star this repository! It really motivates me to make better explanations and produce more work!!** ⭐️

## Overview

This repository contains several C programs that perform different tasks:

1. `caesar.c` - A program that encrypts messages using the Caesar cipher.
2. `readability.c` - A program that determines the readability grade level of a given text using the Coleman-Liau index.
3. `scrabble.c` - A program that simulates a simple game of Scrabble between two players.
4. `substitution.c` - A program that encrypts messages using a substitution cipher.

## Description

### 1. `caesar.c`

#### Purpose

The `caesar.c` program encrypts messages using the Caesar cipher.

#### How it Works

1. The user provides a non-negative integer key via command-line arguments.
2. The program prompts the user for plaintext.
3. Each letter in the plaintext is shifted according to the key.
4. The resulting ciphertext is printed.

#### Key Points

- Validates that the key is a non-negative integer.
- Shifts both uppercase and lowercase letters.
- Leaves non-alphabetic characters unchanged.
- Utilizes functions like `isdigit`, `isalpha`, and `isupper` from `ctype.h`.

### 2. `readability.c`

#### Purpose

The `readability.c` program determines the readability grade level of a given text using the Coleman-Liau index.

#### How it Works

1. The program prompts the user to enter the text.
2. It counts the number of letters, words, and sentences in the text.
3. It calculates the average number of letters per 100 words and the average number of sentences per 100 words.
4. It computes the Coleman-Liau index and prints the grade level.

#### Key Points

- Uses the Coleman-Liau index formula: `index = 0.0588 * L - 0.296 * S - 15.8`.
- Outputs "Before Grade 1" for very simple texts and "Grade 16+" for very complex texts.

### 3. `scrabble.c`

#### Purpose

The `scrabble.c` program simulates a simple game of Scrabble between two players.

#### How it Works

1. Each player inputs a word.
2. The program calculates the score for each word based on Scrabble letter values.
3. It determines the winner based on the scores and prints the result.

#### Key Points

- Defines a points array for each letter of the alphabet.
- Converts letters to lowercase to handle case insensitivity.
- Uses `isalpha` to ensure only alphabetic characters contribute to the score.

### 4. `substitution.c`

#### Purpose

The `substitution.c` program encrypts messages using a substitution cipher.

#### How it Works

1. The user provides a 26-character key via command-line arguments.
2. The program validates the key to ensure it contains 26 unique alphabetic characters.
3. The program prompts the user for plaintext.
4. Each letter in the plaintext is mapped to a different letter in the ciphertext based on the key.
5. The resulting ciphertext is printed.

#### Key Points

- Handles both uppercase and lowercase letters.
- Leaves non-alphabetic characters unchanged.
- Utilizes functions like `isalpha`, `tolower`, `toupper`, and `strcat` from `ctype.h` and `string.h`.

## Credits

<table>
  <tr>
    <td><img src="images/CS50x_logo.png" alt="CS50 Logo" width="800" height="300"></td>
    <td>
      <h3>Credits to CS50x</h3>
      <p>This project was inspired by and developed as part of the CS50x course offered by Harvard University. CS50x is Harvard University's introduction to the intellectual enterprises of computer science and the art of programming for majors and non-majors alike, with or without prior programming experience.</p>
      <ul>
        <li><strong>Course:</strong> CS50x: Introduction to Computer Science</li>
        <li><strong>Institution:</strong> Harvard University</li>
        <li><strong>Instructor:</strong> David J. Malan</li>
        <li><strong>Website:</strong> <a href="https://cs50.harvard.edu/x/2024/">CS50x Official Site</a></li>
      </ul>
      <p>Thank you to the CS50x team for providing such a comprehensive and engaging introduction to computer science.</p>
    </td>
  </tr>
</table>
