#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main()
{
    float change;
    do{
        change = get_float("change owed: ");
    }while (change < 0);
    float cents = change * 100;
    int n=0;


    while(cents >= 25)
    {
        cents = cents - 25;
        n++;
    }

    while(cents >= 10)
    {
        cents = cents - 10;
        n++;
    }

    while(cents >= 5)
    {
        cents = cents - 5;
        n++;
    }

    while(cents >= 1)
    {
        cents = cents - 1;
        n++;
    }

    printf("%i\n", n);


}