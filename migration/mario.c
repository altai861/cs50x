#include <stdio.h>
#include <cs50.h>

void print(int x)
{
    for(int i = 0; i < x; i++)
    {
        printf(" ");
    }
}

void printslash(int y)
{
    for(int i = 0; i < y; i++)
    {
        printf("#");
    }
}

int main()
{
    int height;
    do
    {
        height = get_int("height: ");
    }while(height < 1);

    for(int i = 1; i < height + 1; i++)
    {
        int n = height - i;
        print(n);
        printslash(i);
        printf("  ");
        printslash(i);
        printf("\n");
    }
}