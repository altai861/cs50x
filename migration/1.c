#include <stdio.h>
#include <cs50.h>
#include <math.h>

int checklength(long long cn);
void checksum(long long cn);
long poweroften(int n);



int main()
{
    int sum = 0;
    long long number = get_long_long("number: ");
    int length = checklength(number);

    checksum(number);

}

int checklength(long long cn)
{
    int n = 0;
    while(cn > 0)
    {
        cn = cn / 10;
        n++;
    }
    return n;
}

void checksum(long long cn)
{
    int sum1 = 0;
    int sum2 = 0;
    int length = checklength(cn);


    for (int i = length ; i >= 0 ; i = i - 2)
    {
        sum1 = sum1 + ((int)(cn / poweroften( i - 1)) % 10);
        printf("%i\n", sum1);
    }

    for (int i = length ; i > 0; i = i - 2)
    {
        sum2 = sum2 + ((cn / poweroften( i - 2)) % 10);
    }
    int endingvalue = (sum1 * 2) + sum2;
    //("%i\n", sum1);
    //printf("%i\n", sum2);

    printf("%i\n", endingvalue);

    if (endingvalue % 10 == 0)
    {
        printf("true");
    }
    else
    {
        printf("false");
    }
}


long poweroften(int n)
{
    long ten = 1;
    for(int i = 1; i <= n; i++)
    {
        ten = ten * 10;
    }
    return ten;
}







