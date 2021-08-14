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
    // ranks[i] is voter's ith preference
    

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
    int i;
    for (i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // update the ranks array to indicate that the voter has the candidate as
            // their rank preference (where 0 is the first preference,
            // 1 is the second preference

            // recall that ranks[i] here represents the user’s ith preference
            ranks[rank] = i;
            // ranks[rank] returns the index of the candidate
            return true;
        }

    }
    return false;
}

// Update preferences given one voter's ranks
// take ranks and update the global preferences variable

// called once for each voter and takes input user's ranks
void record_preferences(int ranks[])
{
    // First, notice the two-dimensional array preferences. 
    // The integer preferences[i][j] will represent the number of 
    // voters who prefer candidate i over candidate j.

    // ranks[rank] returns candidate ID
    int i, j;

    for (int rank = 0; rank < candidate_count; rank ++)
    {
        for (int inner = (rank + 1); inner < candidate_count; inner++)
        {
            // printf("prefers id %i over id %i\n", X, Y);
            // printf("candidate %i, huh %i\n", ranks[rank], ranks[inner]);
            preferences[ranks[rank]][ranks[inner]] += 1;
        }

    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Array of all pairs where one candidate is preferred above another

    // Add each pair of candidates to pairs array if 
    // one candidate if preferred over the other

    // Update global variable pair_count to be total number of pairs

    // maybe compare preferences[i][j] and preferences[j][i] see who wins

    int i = 0;
    for (int can1 = 0; can1 < candidate_count; can1 ++)
    {
        for (int can2 = (can1 + 1); can2 < candidate_count; can2++)
        {
            int can1_result = preferences[can1][can2];
            int can2_result = preferences[can2][can1];
            if (can1_result > can2_result)
            { 
                pairs[i].winner = can1;
                pairs[i].loser = can2;
                pair_count += 1;
                i++;
            }
            else if (can1_result < can2_result)
            {
                pairs[i].winner = can2;
                pairs[i].loser = can1;
                pair_count += 1;
                i++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int check_strength = preferences[pairs[i].winner][pairs[i].loser];
        printf("%i\n", check_strength);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

// to get a certain place do ranks[rank]
    // ranks[0] will get first choice candidate
    // int i, j;

    // // query through EACH voter
    // for (i = 0; i < voter_count; i++)
    // {
    //     // for each voter
    //     // loop through their preferences
    //     for (j = 0; j < candidate_count; j++)
    //     {
    //         preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]];
    //         // preferences[i][j] returns the rank
    //     }

    // }
    //preferences[0][0] gives first choice of first voter
    // first [x] is the ranking place and second [x] is candidate ID
    // printf("Test: %i\n", preferences[0][2]);

       // For each voter
    // int i, j;
    // for (i = 0; i < voter_count; i++)
    // {
    //     // For each rank, print candidate
    //     for (j = 0; j < candidate_count; j++)
    //     {
    //         printf("Rank %i: ID %i\n", j, preferences[i][j]);
        
    //     }
    //     printf("\n");
    // }

     // loop over the rankings 
    // for (int rank = 0; rank < candidate_count; rank ++)
    // {
    //     for (int left = candidate_count; left > 0; left--)
    //     {
    //         // printf("prefers id %i over id %i\n", X, Y);
    //         printf("rank %i left %i\n", ranks[rank], left);
    //     }
        
    // }