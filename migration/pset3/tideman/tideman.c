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


typedef struct
{
    int current_max;
    int numberofthecandidate;
}
winner;

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
int totalpair(int candidate_count);
bool checkcycle(bool lockedclone[MAX][MAX]);



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
            preferences[i][j] = 0;
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
    // TODO
    int name_number;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            name_number = i + 1;
            ranks[rank] = name_number;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = totalpair(candidate_count);
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int t = 0;
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[t].winner = i;
                pairs[t].loser = j;
                t = t + 1;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[t].winner = j;
                pairs[t].loser = i;
                t = t + 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count - 1; i++)
    {

        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
        {
            pair swap = pairs[i];
            pairs[i] = pairs[i + 1];
            pairs[i + 1] = swap;
        }

    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {

        locked[pairs[i].winner][pairs[i].loser] = true;
        if (checkcycle(locked))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
            break;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    winner candidate;
    candidate.current_max = 0;
    candidate.numberofthecandidate = 0;

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            int n = 0;
            if (locked[i][j] == true)
            {
                n++;
            }
            if (j == pair_count - 1)
            {
                if (n > candidate.current_max)
                {
                    candidate.current_max = n;
                    candidate.numberofthecandidate = i;
                }
            }
        }
    }
    printf("%s\n", candidates[candidate.numberofthecandidate]);
    return;
}

int totalpair(int candidatecount)
{
    candidatecount = candidate_count - 1;
    int total = 0;
    for (int i = candidatecount; i > 0; i--)
    {
        total = total + candidatecount;
    }
    return total;
}


bool checkcycle(bool lockedclone[MAX][MAX])
{
    lockedclone = locked;
    int n = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0 ; j < pair_count; j++)
        {
            if (lockedclone[i][j] == true)
            {
                n++;
                break;
            }
        }
    }
    if (n == pair_count)
    {
        return true;
    }
    return false;
}