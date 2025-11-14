// Simulate genetic inheritance of blood type

#include <stdbool.h>  // For boolean type
#include <stdio.h>    // For file operations and standard I/O functions
#include <stdlib.h>   // For memory allocation and utility functions
#include <time.h>     // For seeding the random number generator

// Define a structure to represent each person in the family
typedef struct person
{
    struct person *parents[2];  // Pointers to the person's two parents
    char alleles[2];           // Alleles for the person's blood type
} person;

const int GENERATIONS = 3;    // Number of generations to simulate
const int INDENT_LENGTH = 4;  // Number of spaces for indentation in the family tree output

// Function prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed the random number generator with the current time
    srand(time(0));

    // Create a new family tree with the specified number of generations
    person *p = create_family(GENERATIONS);

    // Print the family tree showing blood types
    print_family(p, 0);

    // Free the memory allocated for the family tree
    free_family(p);

    return 0;  // Exit successfully
}

// Create a new family with the specified number of generations
person *create_family(int generations)
{
    // Allocate memory for a new person
    person *new_person = malloc(sizeof(person));
    if (new_person == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);  // Exit with error code if memory allocation fails
    }

    // If there are more generations to create
    if (generations > 1)
    {
        // Recursively create two parents for the current person
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Set the parent pointers for the current person
        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        // Randomly assign the current person's alleles based on their parents' alleles
        new_person->alleles[0] = parent0->alleles[rand() % 2];
        new_person->alleles[1] = parent1->alleles[rand() % 2];
    }
    else
    {
        // If this is the base generation (no more parents), set parent pointers to NULL
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        // Randomly assign alleles for the base generation person
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    // Return the newly created person
    return new_person;
}

// Free the memory allocated for a person and all their ancestors
void free_family(person *p)
{
    // Base case: if the person is NULL, return
    if (p == NULL)
    {
        return;
    }

    // Recursively free the memory for the person's parents
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free the memory for the current person
    free(p);
}

// Print each family member's blood type and their generation
void print_family(person *p, int generation)
{
    // Base case: if the person is NULL, return
    if (p == NULL)
    {
        return;
    }

    // Print indentation based on the generation level
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print information about the person based on their generation
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print the parents of the current person
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele (A, B, or O)
char random_allele()
{
    int r = rand() % 3;  // Generate a random number between 0 and 2
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
