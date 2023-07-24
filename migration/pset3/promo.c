#include <stdio.h>
#include <cs50.h>


typedef struct
{
    int winner;
    int loser;
}
pair;

#define MAX 9
pair pairs[MAX * (MAX - 1) / 2];

int main(void)
{
    int length;

    pairs[0].winner = 2;
    pairs[0].loser = 3;
    for (int i = 0; i < MAX * (MAX - 1) / 2; i++ )
    {
        length = i;
        if (pairs[i].winner == pairs[i].loser)
        {
            break;
        }
    }
    printf("%i", length);
}

