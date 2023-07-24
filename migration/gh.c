#include <stdio.h>
#include <cs50.h>

bool check(int num);


int main(void)
{
    int number = get_int("number: ");
    if (check(number))
    {
        printf("prime");
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