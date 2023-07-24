#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <math.h>


int digitcheck(long long number)
{
    int howmanydigits = 0;
    for (long long i = number; i > 0; i = i / 10 )
    {
        howmanydigits++;
    }
    if (number == 0)
    {
        howmanydigits++;
    }
    return howmanydigits;
}

long long poweroften(int n)
{
    long long result = 1;
    for (int i = 0; i < n; i++)
    {
        result  = result * 10;
    }
    return result;
}


int main(void)
{
    long long cardnumber = get_long("Number: ");
    int digit = digitcheck(cardnumber);
    int firstsum = 0;
    int secondsum = 0;

    // to find the first sum of the formula
    if (digit % 2 == 0)
    {
        for(int i = 2; i <= digit; i = i + 2)
        {
            int number = cardnumber % poweroften(i) / poweroften(i - 1);
            int productnumber = number * 2;
            if(digitcheck(productnumber) == 2)
            {
                int firstpart = productnumber / 10;
                int secondpart = productnumber - (firstpart * 10);
                firstsum = firstsum + firstpart + secondpart;
            }
            else
            {
                firstsum = firstsum + productnumber;
            }
        }
    }
    else
    {
        for(int i = 1; i <= digit; i = i + 2)
        {
            int number = cardnumber % poweroften(i) / poweroften(i - 1);
            int productnumber = number * 2;
            if(digitcheck(productnumber) == 2)
            {
                int firstpart = productnumber / 10;
                int secondpart = productnumber - (firstpart * 10);
                firstsum = firstsum + firstpart + secondpart;
            }
            else
            {
                firstsum = firstsum + productnumber;
            }
        }
    }



    // to find the second sum of the formula
    if (digit % 2 == 0)
    {
        for(int i = 1; i <= digit; i = i + 2)
        {
            int number = cardnumber % poweroften(i) / poweroften(i - 1);
            secondsum = secondsum + number;
        }
    }
    else
    {
        for(int i = 2; i <= digit; i = i + 2)
        {
            int number = cardnumber % poweroften(i) / poweroften(i - 1);
            secondsum = secondsum + number;
        }
    }
    int total = firstsum + secondsum;


    long long first2digits = cardnumber;
    while (first2digits >= 100)
    {
        first2digits = first2digits / 10;
    }

    if (total % 10 == 0)
    {
        if (digit == 13 || digit == 14 || digit == 15 || digit == 16)
        {
            if (first2digits == 40 || first2digits == 41 || first2digits == 42 || first2digits == 43 || first2digits == 44 || first2digits == 45 || first2digits == 46 || first2digits == 47 || first2digits == 48 || first2digits == 49 )
            {
                printf("VISA\n");

            }
        }

        if (digit == 15)
        {
            if (first2digits == 34 || first2digits == 37)
            {
                printf("AMEX\n");

            }
        }
        if (digit == 16)
        {
            if (first2digits == 51 || first2digits == 52 || first2digits == 53 || first2digits == 54 || first2digits == 55)
            {
                printf("MASTERCARD\n");
            }


        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }
}