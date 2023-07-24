#include <stdio.h>
#include <cs50.h>

bool checkprime(long long int num);


int main(void)
{
    long long int num = 600851475143;
    for (long long int i = num / 2; i > 0; i--)
    {
        if (num % i == 0)
        {
            if(checkprime(i))
            {
                printf("%lli\n", i);
                break;
            }
        }

    }
}
bool checkprime(long long int num)
{
    int m = 0;
    for (long long int i = num / 2; i > 1; i-- )
    {
        if (num % i == 0)
        {
            m++;
        }
    }
    if (m == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}