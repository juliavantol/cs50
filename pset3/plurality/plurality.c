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

    // Display winner of election
    print_winner();

}

// Update vote totals given a new vote
bool vote(string name)
{
    // See if the name is in the candidate array and if so, add 1 to their votes
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
    // Sort the candidates so the highest scores go in front of the array
    int i, j, placeholder_votes;
    string placeholder_name;
    for (i = 0; i < candidate_count; ++i) 
    {
        for (j = i + 1; j < candidate_count; ++j) 
        {
            if (candidates[i].votes < candidates[j].votes) 
            {
                placeholder_votes = candidates[i].votes;
                candidates[i].votes = candidates[j].votes;
                candidates[j].votes = placeholder_votes;

                placeholder_name = candidates[i].name;
                candidates[i].name = candidates[j].name;
                candidates[j].name = placeholder_name;
            }
        }
    }

    // Print the first name in the array aka the one with the highest amount of votes
    printf("%s\n", candidates[0].name);

    // Look if there are other candidates that share the highest amount of votes of number 1
    // Stop immediately if the second one isn't the same score as number 1 cause that means all
    // others will be lower as well
    int x;
    for (x = 1; x < candidate_count; ++x) 
    {
        if (candidates[0].votes == candidates[x].votes) 
        {
            printf("%s\n", candidates[x].name);
        }
        else 
        {
            break;
        }
    }
}