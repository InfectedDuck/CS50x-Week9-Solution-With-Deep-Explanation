#include <cs50.h>        // Include the CS50 library for user input functions
#include <stdio.h>       // Include the standard input/output library for printing and reading
#include <string.h>      // Include the string library for string manipulation functions
#include <stdbool.h>     // Include the stdbool library for boolean data type

// Define constants for maximum number of voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// 2D array to store preferences: preferences[i][j] is the jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Define a structure for candidates with a name, vote count, and elimination status
typedef struct
{
    string name;         // Name of the candidate
    int votes;           // Number of votes received by the candidate
    bool eliminated;     // Status of whether the candidate is eliminated
} candidate;

// Array to store candidates
candidate candidates[MAX_CANDIDATES];

// Variables to store the number of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);   // Function to record a vote
void tabulate(void);                           // Function to count votes
bool print_winner(void);                       // Function to print the winner of the election
int find_min(void);                           // Function to find the minimum vote count
bool is_tie(int min);                         // Function to check if the election is tied
void eliminate(int min);                      // Function to eliminate candidates with minimum votes

int main(int argc, string argv[])
{
    // Check for invalid usage: at least one candidate name must be provided
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1; // Exit with status 1 to indicate an error
    }

    // Initialize array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2; // Exit with status 2 to indicate an error
    }
    
    // Set up candidate names and initial vote counts
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; // Set candidate name from command-line arguments
        candidates[i].votes = 0;          // Initialize vote count to 0
        candidates[i].eliminated = false; // Set elimination status to false
    }

    // Get the number of voters
    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3; // Exit with status 3 to indicate an error
    }

    // Query each voter for their preferences
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1); // Get the preferred candidate name for this rank

            // Record the vote if valid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4; // Exit with status 4 to indicate an error
            }
        }

        printf("\n"); // Print a newline after each voter's input
    }

    // Continue holding runoffs until a winner is determined
    while (true)
    {
        tabulate(); // Count the votes for each candidate

        // Check if there's a winner
        bool won = print_winner();
        if (won)
        {
            break; // Exit the loop if a winner is found
        }

        // Find the candidate(s) with the minimum number of votes
        int min = find_min();
        bool tie = is_tie(min);

        // If there's a tie, print all remaining candidates
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break; // Exit the loop if there's a tie
        }

        // Eliminate candidates with the minimum number of votes
        eliminate(min);

        // Reset vote counts to zero for the next round
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }

    return 0; // Exit with status 0 to indicate successful completion
}

// Function to record a voter's preference
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate name matches the provided name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Record the candidate index for this voter's preference
            preferences[voter][rank] = i;
            return true; // Return true to indicate a successful vote
        }
    }
    return false; // Return false if no matching candidate was found
}

// Function to count votes for non-eliminated candidates
void tabulate(void)
{
    // Loop through each voter
    for (int j = 0; j < voter_count; j++)
    {
        // Loop through each preference rank
        for (int i = 0; i < candidate_count; i++)
        {
            // Get the candidate index from preferences
            int candidate_index = preferences[j][i];
            
            // If the candidate is not eliminated, count the vote
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes += 1;
                break; // Only count the highest-ranked non-eliminated candidate
            }
        }
    }
}

// Function to print the winner of the election, if any
bool print_winner(void)
{
    // Loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate has more than half of the total votes
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name); // Print the winner's name
            return true; // Return true to indicate a winner was found
        }
    }
    return false; // Return false if no winner was found
}

// Function to find the minimum number of votes any remaining candidate has
int find_min(void)
{
    int mini = 10000; // Initialize minimum vote count to a large value

    // Loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Update minimum vote count if current candidate has fewer votes and is not eliminated
        if (candidates[i].votes < mini && !candidates[i].eliminated)
        {
            mini = candidates[i].votes;
        }
    }
    return mini; // Return the minimum vote count
}

// Function to check if the election is tied between all remaining candidates
bool is_tie(int min)
{
    // Loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if any non-eliminated candidate does not have the minimum vote count
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false; // Return false if there's no tie
        }
    }
    return true; // Return true if all remaining candidates have the same vote count
}

// Function to eliminate the candidate(s) with the minimum number of votes
void eliminate(int min)
{
    // Loop through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Eliminate candidates with the minimum vote count
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
