#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int voter_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool is_cycle(int loser, int winner);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    voter_count = get_int("Number of voters: ");    

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }
   
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If the name is in the candidates array, update ranks
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop through their rankings
    for (int rank = 0; rank < candidate_count; rank ++)
    {
        for (int inner = (rank + 1); inner < candidate_count; inner++)
        {
            // Update preferences array to add their preferences
            preferences[ranks[rank]][ranks[inner]] += 1;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int i = 0;
    for (int can1 = 0; can1 < candidate_count; can1 ++)
    {
        for (int can2 = (can1 + 1); can2 < candidate_count; can2++)
        {
            // Calculate how many prefer one pairing over the other
            // Compare the results and see who wins
            int can1_result = preferences[can1][can2];
            int can2_result = preferences[can2][can1];

            // Add each pair of candidates to pairs array if one candidate if preferred over the other
            if (can1_result > can2_result)
            { 
                pairs[i].winner = can1;
                pairs[i].loser = can2;

                // Update pair_count to be total number of pairs
                pair_count += 1;
                i++;
            }
            else if (can1_result < can2_result)
            {
                pairs[i].winner = can2;
                pairs[i].loser = can1;

                // Update pair_count to be total number of pairs
                pair_count += 1;
                i++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            // Calculate strength of victory of both pairs
            int strength1 = preferences[pairs[i].winner][pairs[i].loser];
            int strength2 = preferences[pairs[j].winner][pairs[j].loser];
            
            // Swap if the one on the right is a higher value
            if (strength1 < strength2)
            {
                int placeholder_winner = pairs[i].winner;
                int placeholder_loser = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;

                pairs[j].winner = placeholder_winner;
                pairs[j].loser = placeholder_loser;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Go through the pairs one at the time and lock them in the graph
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // If the function that checks if it will create a cycle returns false, lock the pair
        if (is_cycle(loser, winner) == false)
        {
            locked[winner][loser] = true;
        }
    }
}

// Check if a cycle will be created
bool is_cycle(int loser, int winner)
{
    // If an instance points at itself, cycle is created
    if (winner == loser)
    {
        return true;
    }

    // Check through locked pairs if the current loser has won somewhere
    for (int i = 0; i < candidate_count; i++)
    {
        // If the current loser has been found to win somewhere else, run function again
        if (locked[loser][i] == true)
        {
            if (is_cycle(i, winner) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Find the person who doesn't have any arrows pointed to them
    for (int potential_winner = 0; potential_winner < candidate_count; potential_winner++)
    {
        // Keep count of how many times a candidate lost
        int lost_count = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][potential_winner] == true)
            {
                lost_count++;
            }
        }

        // If they never lost, no arrows are pointing to them thus they are the winner
        if (lost_count == 0)
        {
            printf("%s\n", candidates[potential_winner]);
        }
    }
}