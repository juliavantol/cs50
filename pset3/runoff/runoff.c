#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
// The array preferences[i] will represent all of the preferences for 
// voter number i
// integer preferences[i][j] here will store the index of the 
// candidate who is the jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];


// Numbers of voters and candidates
int voter_count;
int candidate_count;
int active_runners;
bool winners = false;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    active_runners = candidate_count;

    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes for each voter
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            // Record vote, unless it's invalid
            // i = voter j = rank
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();
        
        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // See if the name is in the candidate array and if so, add 1 to their votes
    for (int i = 0; i < candidate_count; i++)
    {   
        // Check if the name is in the array of candidates
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Link the candidate(i) with their rank
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int i, j, highest;
    bool nothing_left = true;
    for (i = 0; i < voter_count; i++) 
    {   
        // Check for highest remaining candidate, initially their first preference is at 0 so top = 0
        int top = 0; 
        for (j = 0; j < 3; j++)
        {
            // Check the preferred candidate, if they're eliminated; look to the next rank otherwise break the loop
            highest = preferences[i][top];
            if (candidates[highest].eliminated == true)
            {
                top += 1;
            }
            else
            {
                nothing_left = false;
                break;
            }
        }

        if (nothing_left == false)
        {
            // Add vote to the most preferred candidate who isn't eliminated
            candidates[highest].votes += 1;
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int i;
    // Loop through all the candidates
    for (i = 0; i < candidate_count; i++)
    {
        // If the candidate has the majority of votes, print their name and return true
        if (candidates[i].votes > (voter_count / 2))
        {
            string winner = candidates[i].name;
            printf("%s\n", winner);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Set lowest number variable initially to a number that will be higher than anyone's votes
    int lowest_number = (MAX_CANDIDATES + 1);
    int i;
    // Loop through the candidates
    for (i = 0; i < candidate_count; i++)
    {   
        // If the candidate isn't eliminated & amount of votes is lower than the current lowest numbber
        if (!candidates[i].eliminated && candidates[i].votes < lowest_number)
        {
            // Set lowest number to their amount of votes
            lowest_number = candidates[i].votes;
        }
    }
    return lowest_number;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int i;
    for (i = 0; i < candidate_count; i++)
    {   
        // Return false if amount of votes don't match or if they aren't eliminated
        if (candidates[i].votes != min && candidates[i].eliminated == false)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    int i;
    for (i = 0; i < candidate_count; i++)
    {   
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        } 
    }
}