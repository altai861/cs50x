#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>


void hurdle(int h);


int main(void)
{
   int height;
   printf("height: ");
   scanf("%i\n", &height);

   hurdle(height);




}

void hurdle(int h)
{
   if (h == 0)
   {
      return;
   }

   hurdle(h - 1);

   for (int i = 0; i < h; i++)
   {
      printf("#");
   }
   printf("\n");
}