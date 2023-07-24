#include <stdio.h>
#include <cs50.h>

bool check(int num);


int main(void)
{
    int number = 838;
    if (check(number))
    {
        printf("sdasd");
    }
    int product = 0;
    for (int i = 999; i > 99; i--)
    {
        for (int j = 999; i > 99; i--)
        {
            if (check(i * j))
            {
                printf("%i\n", i * j);
            }
        }
    }

}
bool check(int num)
{
    int currentdigit = 0;
    int reversed = 0;
    int copynumber = num;

    do
    {
        currentdigit = copynumber % 10;
        reversed = (reversed * 10) + currentdigit;
        copynumber = copynumber / 10;
    }while (num != 0);


    if (reversed == num )
    {
        return true;
    }
    else
    {
        return false;
    }
}