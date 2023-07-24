#include <stdio.h>
#include <cs50.h>
#include <string.h>

int how_many_sentences(string text);

int main(void)
{
    string s = " stradasd sadasdasda. asdasdasd.";
    int letter = how_many_sentences(s);
    printf("%i\n", letter);
}

int how_many_sentences(string text)
{
    int sum = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sum++;
        }
    }
    return sum;

}
