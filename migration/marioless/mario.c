#include <cs50.h>
#include <stdio.h>

void printspace(int n);
void printslash(int n);


void printspace(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

void printslash(int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }while(height <= 0);


    for (int i = 1; i <= height; i++)
    {
        printspace(height - i);
        printslash(i);
    }
}