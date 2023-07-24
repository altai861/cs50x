#include <stdio.h>
#include <cs50.h>

int fib(int n);

int main(void)
{
    long t1 = 1, t2 = 2, next = 0;
    long long sum = 0;

    while (next <= 4000000)
    {
        if (next % 2 == 0)
        {
            sum += next;
        }
        next = t2 + t1;
        t1 = t2;
        t2 = next;

    }
    printf("%lli\n", sum + 2);
}

int fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}