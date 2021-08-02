#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    printf("\n");

    // Display winner of election
    print_winner();

}

// Update vote totals given a new vote
bool vote(string name)
{
    // find someone
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // sort
    int i, j, a;
    string b;
    for (i = 0; i < candidate_count; ++i) 
    {
        for (j = i + 1; j < candidate_count; ++j) 
        {
            if (candidates[i].votes < candidates[j].votes) 
            {
                a = candidates[i].votes;
                candidates[i].votes = candidates[j].votes;
                candidates[j].votes = a;

                b = candidates[i].name;
                candidates[i].name = candidates[j].name;
                candidates[j].name = b;
            }
        }
    }

    printf("%s\n", candidates[0].name);
    int x;

    for (x = 1; x < candidate_count; ++x) 
    {
        if (candidates[0].votes == candidates[x].votes) 
        {
            printf("%s\n", candidates[x].name);
        }
        
    }

}

