#include <stdio.h>
#include <cs50.h>

long long int poweroften(int n);
int checklength(long long int cn);


int main()
{
    long long int n = get_long_long("number: ");
    int length = checklength(n);
    int sum1 = 0;
    int sum2 = 0;

    if (length % 2 == 0)
    {
        for (int i = 1; i < length; i = i + 2)
        {
            int j = n / poweroften(i);
            sum1 = sum1 + j % 10;
        }
    }
    printf("%i\n", sum1);

}


long long int poweroften(int n)
{
    long long ten = 1;
    for(int i = 1; i <= n; i++)
    {
        ten = ten * 10;
    }
    return ten;
}

int checklength(long long int cn)
{
    int n = 0;
    while(cn > 0)
    {
        cn = cn / 10;
        n++;
    }
    return n;
}