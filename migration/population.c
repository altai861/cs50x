#include <stdio.h>
#include <cs50.h>

int main(void)
{

    // TODO: Prompt for start size
    int pop, end, update;

    do
    {
        pop = get_int("Enter your population size: ");
    }while(pop < 9);

    // TODO: Prompt for end size
    do
    {
        end = get_int("Enter your end size: ");
    }while(end < pop);

    // TODO: Calculate number of years until we reach threshold
    int n = 0;
    while(pop < end)
    {
        pop = pop + pop/3 - pop/4;
        n++;
    }


    // TODO: Print number of years
    printf("Years: %i\n", n);
}

