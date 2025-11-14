#include <cs50.h>  // CS50 library for getting input from users
#include <stdio.h> // Standard I/O library for input and output functions
#include <string.h> // Standard library for string manipulation functions

// Define the maximum number of candidates that the program can handle
#define MAX 9

// 2D array to keep track of how many voters prefer candidate i over candidate j
int preferences[MAX][MAX];

// 2D array to represent the locked pairs graph; locked[i][j] is true if candidate i is locked in over candidate j
bool locked[MAX][MAX];

// Structure to represent a pair of candidates in the election
typedef struct
{
    int winner; // Index of the candidate who is preferred
    int loser;  // Index of the candidate who is less preferred
} pair;

// Array to store the names of the candidates
string candidates[MAX];
// Array to store all pairs of candidates; size is calculated as MAX * (MAX - 1) / 2
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;      // Variable to keep track of the number of pairs
int candidate_count; // Variable to keep track of the number of candidates

// Function prototypes for various steps in the Tideman voting algorithm
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid command-line usage; there must be at least one candidate
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate the array of candidates from command-line arguments
    candidate_count = argc - 1; // Number of candidates is the number of command-line arguments minus one
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    
    // Assign candidate names from command-line arguments
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Initialize the locked array to false; no pairs are locked initially
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;  // Initialize the number of pairs to zero
    int voter_count = get_int("Number of voters: ");  // Get the number of voters from the user

    // Query each voter for their preferences
    for (int i = 0; i < voter_count; i++)
    {
        // Array to store each voter's preferences; ranks[i] represents the ith preference
        int ranks[candidate_count];

        // Query each rank for the current voter
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);  // Get the name of the candidate for the given rank

            // Record the vote; if the vote is invalid, print an error message and exit
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        // Update preferences based on the voter's ranks
        record_preferences(ranks);

        printf("\n");  // Print a newline for readability
    }

    // Process the votes to determine the winner
    add_pairs();   // Determine all pairs of candidates based on preferences
    sort_pairs(); // Sort pairs in order of strength of victory
    lock_pairs(); // Lock pairs into the graph, ensuring no cycles
    print_winner(); // Print the winner(s) of the election

    return 0;
}

// Update ranks array given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate over all candidates to find the index of the candidate named 'name'
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)  // Compare the given name with candidate names
        {
            ranks[rank] = i;  // Store the index of the candidate in the ranks array
            return true;     // Return true if the vote was successfully recorded
        }
    }
    return false;  // Return false if the candidate name was not found
}

// Update preferences matrix given one voter's ranks
void record_preferences(int ranks[])
{
    // Iterate over all pairs of candidates based on the voter's ranks
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Increment the preference count for the pair (ranks[i], ranks[j])
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate over all possible pairs of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && preferences[i][j] > preferences[j][i])  // Check if candidate i is preferred over candidate j
            {
                // Store the pair with candidate i as the winner and candidate j as the loser
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;  // Increment the count of pairs
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Iterate over all pairs to sort them
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            // Calculate the strength of victory for the pairs at indices i and j
            int s_i = preferences[pairs[i].winner][pairs[i].loser];
            int s_j = preferences[pairs[j].winner][pairs[j].loser];
            // Swap pairs if the pair at index j has a stronger victory
            if (s_i < s_j)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
}

// Helper function to check for cycles in the locked graph
bool cyclic(int start, int curr)
{
    if (curr == start)  // If the current candidate is the start candidate, a cycle is detected
        return true;

    // Check all candidates for a cycle
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[curr][i] && cyclic(start, i))  // If a cycle is detected from the current candidate
            return true;
    }
    return false;  // No cycle detected
}

// Lock pairs into the candidate graph in order, avoiding cycles
void lock_pairs(void)
{
    // Iterate over all pairs and lock them if they don't create a cycle
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;  // Index of the winner candidate
        int l = pairs[i].loser;   // Index of the loser candidate
        // Lock the pair if it does not create a cycle
        if (!cyclic(w, l))
        {
            locked[w][l] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Iterate over all candidates to find the source (candidate with no incoming edges)
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true;  // Assume the candidate is a source until proven otherwise
        // Check if the current candidate is the source
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])  // If any candidate has an edge pointing to the current candidate
            {
                source = false;  // Current candidate is not the source
                break;
            }
        }
        // If the candidate is the source, print the winner and exit
        if (source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
