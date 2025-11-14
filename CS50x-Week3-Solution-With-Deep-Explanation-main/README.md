# README

### ⭐️ **Star this repository! It really motivates me to make better explanations and produce more work!!** ⭐️

## Overview

This repository contains several C programs that implement different algorithms and functionalities:

1. `runoff.c` - A program that implements a runoff election system.
2. `tideman.c` - A program that implements the Tideman voting method.
3. `plurality.c` - A program that implements the plurality voting method.
4. `sort` - A program that demonstrates the implementation of different sorting algorithms: Bubble Sort, Merge Sort, and Selection Sort.

## Description

### 1. `runoff.c`

#### Purpose

The `runoff.c` program implements a runoff election system, where voters rank candidates in order of preference. The program determines the winner through a series of rounds, eliminating candidates with the fewest votes until one candidate achieves a majority.

#### How it Works

1. The user provides the number of candidates and voters via command-line arguments.
2. The program prompts the user for each voter's ranked preferences.
3. In each round, it counts the votes for each candidate, considering only the highest-ranked candidate on each voter's ballot.
4. If no candidate has a majority, the candidate with the fewest votes is eliminated, and votes are redistributed according to the next preference.
5. The process repeats until a candidate has a majority of the votes.

#### Key Points

- Utilizes a series of rounds to determine the winner.
- Handles ranked voting and vote redistribution.
- Implements vote counting and elimination based on the fewest votes.

### 2. `tideman.c`

#### Purpose

The `tideman.c` program implements the Tideman voting method, also known as the ranked pairs method. It determines the winner by considering the strength of each candidate's victories over other candidates.

#### How it Works

1. The user provides the number of candidates and voters via command-line arguments.
2. The program prompts the user for each voter's ranked preferences.
3. It compares each pair of candidates and determines which candidate is preferred in each comparison.
4. The pairs are sorted by the strength of victory.
5. The program locks in pairs one by one, ensuring no cycles are created.
6. The candidate with no incoming edges in the graph is declared the winner.

#### Key Points

- Utilizes pairwise comparisons to determine the strongest victories.
- Sorts pairs by strength and locks them in without creating cycles.
- Determines the winner based on the final graph structure.

### 3. `plurality.c`

#### Purpose

The `plurality.c` program implements the plurality voting method. In this method, each voter selects one candidate, and the candidate with the most votes wins.

#### How it Works

1. The user provides the number of candidates and voters via command-line arguments.
2. The program prompts the user for each voter's choice.
3. It counts the number of votes for each candidate.
4. The candidate with the highest number of votes is declared the winner.

#### Key Points

- Simplest form of voting where each voter has one vote.
- The candidate with the most votes wins.
- Does not handle ties or ranked preferences.

### 4. `sort.c`

#### Purpose

The `sort.c` program demonstrates the implementation of different sorting algorithms: Bubble Sort, Merge Sort, and Selection Sort. Each algorithm is tested with various input scenarios to analyze and compare their performance.

#### How it Works

1. The user provides an array of integers via command-line arguments.
2. The program has several functions that apply each sorting algorithm to the array:
   - **Bubble Sort**: Repeatedly steps through the list, compares adjacent items, and swaps them if they are in the wrong order until the list is sorted.
   - **Merge Sort**: Divides the list into smaller parts, sorts each part, and then merges the sorted parts back together.
   - **Selection Sort**: Finds the minimum element from the unsorted portion of the list and moves it to the beginning.
3. The objective is to determine which sorting algorithm is implemented in each of the provided programs.

#### Key Points

- **Bubble Sort**: Known for its simplicity and best performance on already sorted lists.
- **Merge Sort**: Recognizable by its consistent performance across different data arrangements and divide-and-conquer approach.
- **Selection Sort**: Distinguished by its consistent O(n^2) performance across all scenarios.

#### Sorting Algorithm Analysis

- **Bubble Sort**: Identified by its simple swapping mechanism and best performance on already sorted lists.
- **Merge Sort**: Recognizable by its consistent performance across different data arrangements and divide-and-conquer approach.
- **Selection Sort**: Distinguished by its consistent O(n^2) performance across all scenarios.

## Determining Sorting Algorithms

To identify the sorting algorithm used in each program, follow these steps:

### Setup and Run

1. **Execute each sorting program** with different types of input data:
   - Randomly shuffled arrays
   - Sorted arrays
   - Reversed arrays

### Measure Runtime

1. **Use a timing tool or stopwatch** to record the duration of the sorting process for each input type.
2. **Run each program multiple times** to ensure accurate and consistent results.

### Analyze Results

1. **Bubble Sort**: This algorithm performs best with already sorted data, showing a significant decrease in runtime for sorted arrays compared to random or reversed arrays. It has a worst-case runtime of \( O(n^2) \) for reversed data.

2. **Merge Sort**: Known for its consistent performance across different data types, Merge Sort maintains similar runtimes for random, sorted, and reversed arrays, with a time complexity of \( O(n \log n) \).

3. **Selection Sort**: This algorithm exhibits a consistent runtime regardless of the initial order of the data, reflecting its \( O(n^2) \) time complexity. It usually shows slower performance compared to Merge Sort but can be faster than Bubble Sort for certain scenarios.

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
