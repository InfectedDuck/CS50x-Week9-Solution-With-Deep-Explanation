# README

### ⭐️ **Star this repository! It really motivates me to make better explanations and produce more work!!** ⭐️

## Overview

This repository contains several C programs that perform different tasks:
1. `cash.c` - A program that calculates the minimum number of coins required to give a user change.
2. `credit.c` - A program that checks the validity of a credit card number using Luhn's Algorithm and identifies the type of card (AMEX, MASTERCARD, VISA).
3. `hello.c` - A simple program that prompts the user for their name and prints a greeting.
4. `mario_less.c` - A program that prints a half-pyramid of a specified height using hashes.
5. `mario_more.c` - A program that prints a full pyramid with a gap in the middle of a specified height using hashes.

## Description

### 1. `cash.c`

#### Purpose

The `cash.c` program calculates the minimum number of coins needed to make change for a given amount of money in cents. It uses U.S. coin denominations (quarters, dimes, nickels, and pennies).

#### How it Works

1. The program prompts the user to enter a non-negative amount of change owed.
2. The input is validated to ensure it is non-negative.
3. The program calculates the number of quarters, dimes, nickels, and pennies required to make the change.
4. The total number of coins is printed.

#### Key Points

- Uses U.S. coin denominations: quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).
- Implements a greedy algorithm to minimize the number of coins.

### 2. `credit.c`

#### Purpose

The `credit.c` program validates a credit card number using Luhn's Algorithm and identifies the card type (AMEX, MASTERCARD, VISA).

#### How it Works

1. The program prompts the user to enter a credit card number.
2. It checks the validity of the card number using Luhn's Algorithm.
3. If the card number is valid, it identifies the type of card based on the number's prefix and length.
4. The program prints the card type or "INVALID" if the card number is not valid.

#### Key Points

- Uses Luhn's Algorithm for credit card validation.
- Identifies card type based on prefix and length:
  - AMEX: 15 digits, starts with 34 or 37.
  - MASTERCARD: 16 digits, starts with 51-55.
  - VISA: 13 or 16 digits, starts with 4.

### 3. `hello.c`

#### Purpose

The `hello.c` program prompts the user for their name and then prints a greeting.

#### How it Works

1. The program prompts the user to enter their name.
2. It prints "Hello, [name]" using the entered name.

#### Key Points

- Demonstrates basic input and output operations in C.
- Simple example of user interaction.

### 4. `mario_less.c`

#### Purpose

The `mario_less.c` program prints a half-pyramid of a specified height using hashes.

#### How it Works

1. The program prompts the user to enter a height between 1 and 8.
2. It prints a right-aligned half-pyramid of the specified height.

#### Key Points

- Utilizes loops to print a right-aligned half-pyramid.
- Emphasizes understanding of nested loops and character output.

### 5. `mario_more.c`

#### Purpose

The `mario_more.c` program prints a full pyramid with a gap in the middle of a specified height using hashes.

#### How it Works

1. The program prompts the user to enter a height between 1 and 8.
2. It prints a full pyramid of the specified height with two spaces in the middle.

#### Key Points

- Builds on the concepts from `mario_less.c` to create a more complex pattern.
- Demonstrates control over spacing and alignment in text output.

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
