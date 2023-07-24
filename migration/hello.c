#include <stdio.h>
#include <cs50.h>
#include <math.h>



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
    long long i = 4003600000000014;
    printf("%lli\n", poweroften(3));
}