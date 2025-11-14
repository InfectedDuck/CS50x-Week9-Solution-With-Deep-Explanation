# README

### ⭐️ **Star this repository! It really motivates me to make better explanations and produce more work!!** ⭐️

## Overview

This repository contains several Python programs that perform different tasks:

1. `cash.py` - A program that calculates the minimum number of coins needed to make change.
2. `credit.py` - A program that validates credit card numbers using Luhn's algorithm.
3. `DNA.py` - A program that matches DNA sequences against a database of profiles.
4. `hello.py` - A simple program that greets the user.
5. `mario-less.py` - A program that prints a half-pyramid pattern based on user input.
6. `mario-more.py` - A program that prints a full pyramid pattern based on user input.

## Description

### 1. `cash.py`

#### Purpose

The `cash.py` program calculates the minimum number of coins needed to make change for a given amount of money.

#### How it Works

1. Prompts the user to enter a non-negative amount of change in dollars.
2. Converts the amount to cents.
3. Calculates the number of quarters, dimes, nickels, and pennies needed.
4. Outputs the total number of coins.

#### Key Points

- Handles floating-point precision issues by rounding.
- Uses basic arithmetic operations for coin calculations.

### 2. `credit.py`

#### Purpose

The `credit.py` program checks the validity of credit card numbers using Luhn's algorithm and identifies the card type.

#### How it Works

1. Prompts the user to enter a credit card number.
2. Validates the number using Luhn's algorithm.
3. Identifies the card type (VISA, AMEX, MasterCard) or reports it as invalid.

#### Key Points

- Implements Luhn's algorithm for card validation.
- Checks card type based on length and starting digits.

### 3. `DNA.py`

#### Purpose

The `DNA.py` program identifies individuals based on their DNA sequence by comparing it against a database of profiles.

#### How it Works

1. Reads DNA profiles from a CSV file and a DNA sequence from a text file.
2. Computes the longest run of each STR (Short Tandem Repeat) in the DNA sequence.
3. Matches the longest runs with profiles in the database.
4. Outputs the name of the matching profile or "No match" if none is found.

#### Key Points

- Uses CSV and text file handling.
- Implements a function to find the longest run of a subsequence in a sequence.

### 4. `hello.py`

#### Purpose

The `hello.py` program prompts the user for their name and prints a personalized greeting.

#### How it Works

1. Prompts the user to enter their name.
2. Prints a greeting message that includes the user's name.

#### Key Points

- Simple input and output operations.
- Demonstrates basic string concatenation.

### 5. `mario-less.py`

#### Purpose

The `mario-less.py` program prints a half-pyramid pattern of a specified height.

#### How it Works

1. Prompts the user to enter the height of the pyramid (between 1 and 8).
2. Prints the pyramid with the specified number of rows.

#### Key Points

- Handles user input and validation.
- Uses string multiplication for pattern generation.

### 6. `mario-more.py`

#### Purpose

The `mario-more.py` program prints a full pyramid pattern of a specified height with two aligned halves.

#### How it Works

1. Prompts the user to enter the height of the pyramid (between 1 and 8).
2. Prints the pyramid with two halves, separated by two spaces.

#### Key Points

- Handles user input and validation.
- Uses string multiplication and concatenation for pattern generation.

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
