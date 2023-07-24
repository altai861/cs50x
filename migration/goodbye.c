#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");
    if(x < y)
    {
        printf("y is greater than x\n");
    }
    else if(x > y)
    {
        printf("y is less than x\n");
    }
    else
    {
        printf("y is equal to x\n");
    }
}