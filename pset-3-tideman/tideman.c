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
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
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
        if (strcmp(candidates[i], name) == 0) // is existing candidate
        {
            for (int j = rank-1; j >= 0; j--)
            {
                if (ranks[j] == i) // candidate already picked
                {
                    return false;
                }
            }
        ranks[rank] = i; // add canidate id to ranks
        return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++; // add preference
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j) // if not Alice over Alice for ex.
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++) // selection sort
    {
        int at = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        int found = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            int search = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (search > at)
            {
                at = search;
                found = j;
            }
        }
        if (found > i)
        {
            int temp_winner = pairs[i].winner;
            int temp_loser = pairs[i].loser;
            pairs[i].winner = pairs[found].winner;
            pairs[i].loser = pairs[found].loser;
            pairs[found].winner = temp_winner;
            pairs[found].loser = temp_loser;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {

        int point_to = pairs[i].loser;
        int now = i;
        bool repeat;
        bool pass = true;

        do { // search for parents making the lock impossible
            repeat = false;
            for (int j = 0; j < pair_count; j++)
            {
                if (locked[pairs[j].winner][pairs[now].winner])
                {
                    repeat = true;
                    now = j;
                }
                if (pairs[now].winner == point_to)
                {
                    pass = false;
                    break;
                }
            }
        } while (repeat && pass);

        if (pass) // if no parents that won
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner;
    for (int i = 0; i < candidate_count; i++)
    {
        winner = i;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                winner = -1;
                break;
            }
        }
        if (winner > -1) // if not locked by others
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}