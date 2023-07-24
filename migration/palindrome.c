#include <stdio.h>
#include <cs50.h>





bool isPalindrome(int x);
int poweroften(int power);

bool isPalindrome(int x){
    int counter = 0;
    int sizeofnumber = 0;
    int number = x;

    while(number >= 1)
    {
        number = number / 10;
        sizeofnumber++;
    }


    int revertedNumber = 0;
    while(x > revertedNumber) {
        revertedNumber = revertedNumber * 10 + x % 10;
        x /= 10;
    }

    return x == revertedNumber || x == revertedNumber/10;

}



int poweroften(int power)
{
    int base = 1;
    for (int i = 0; i < power; i++ )
    {
        base= base* 10;
    }
    return base;
}



int main()
{
    if (isPalindrome(121))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
}












