#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (i % 3 == 0 || i % 5 == 0)
        {
            sum = sum + i;
        }

    }
    printf("%i\n", sum);
}
