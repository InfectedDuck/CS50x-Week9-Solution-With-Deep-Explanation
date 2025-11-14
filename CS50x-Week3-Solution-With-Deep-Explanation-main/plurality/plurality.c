#include <cs50.h>        // Include the CS50 library for getting input from the user
#include <stdio.h>       // Include the standard input/output library for printing output
#include <string.h>      // Include the string library for string manipulation functions (e.g., strcmp)
#include <stdbool.h>     // Include the stdbool library for using boolean data type

// Define the maximum number of candidates
#define MAX 9

// Define a structure for candidates with a name and vote count
typedef struct
{
    string name;   // Name of the candidate
    int votes;     // Number of votes received by the candidate
} candidate;

// Array to store candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);    // Function to record a vote for a candidate
void print_winner(void);   // Function to print the winner(s) of the election

int main(int argc, string argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc < 2)
    {
        // Print usage message if there are not enough arguments
        printf("Usage: plurality [candidate ...]\n");
        return 1; // Exit with status 1 to indicate an error
    }

    // Set the number of candidates based on command-line arguments
    candidate_count = argc - 1;

    // Check if the number of candidates exceeds the maximum allowed
    if (candidate_count > MAX)
    {
        // Print an error message if there are too many candidates
        printf("Maximum number of candidates is %i\n", MAX);
        return 2; // Exit with status 2 to indicate an error
    }

    // Initialize the candidates' names and votes
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; // Set candidate name from command-line argument
        candidates[i].votes = 0;          // Initialize vote count to 0
    }

    // Get the number of voters from the user
    int voter_count = get_int("Number of voters: ");

    // Loop through each voter
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: "); // Get the name of the candidate being voted for

        // Record the vote and check for validity
        if (!vote(name))
        {
            // Print an error message if the vote is invalid
            printf("Invalid vote.\n");
        }
    }

    // Display the winner(s) of the election
    print_winner();

    return 0; // Return 0 to indicate successful completion of the program
}

// Function to update vote totals given a new vote
bool vote(string name)
{
    // Loop through each candidate to find a match
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate's name matches the voted name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Increment the vote count for the matched candidate
            candidates[i].votes += 1;
            return true; // Return true to indicate a successful vote
        }
    }
    return false; // Return false if no matching candidate was found
}

// Function to print the winner(s) of the election
void print_winner(void)
{
    int maxi = 0; // Variable to store the highest number of votes
    int index = 0; // Variable to store the index of the candidate with the highest votes

    // Find the candidate(s) with the maximum number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        // Update the maximum votes and index if the current candidate has more votes
        if (maxi < candidates[i].votes)
        {
            maxi = candidates[i].votes;
            index = i;
        }
    }

    // Print the names of the candidate(s) with the maximum number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        // Print the name of the candidate if they have the maximum number of votes
        if (maxi == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
