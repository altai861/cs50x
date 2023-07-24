#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int how_many_letters(string text);
int how_many_words(string text);
int how_many_sentences(string text);



int main(void)
{
    string text = get_string("Text: ");
    int letters = 0;
    int words = 0;
    int sentences = 0;

    letters = how_many_letters(text);
    words = how_many_words(text);
    sentences = how_many_sentences(text);

    int L = (100 * letters) / words;
    int S = (100 * sentences) / words;
    int index = 0.0588 * L - 0.296 * S - 15.8;

    if (round(index) >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(index) );
    }


}

int how_many_letters(string text)
{
    int sum = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if (((int)text[i] >= 65 && (int)text[i] <= 90) || ((int)text[i] >= 97 && (int)text[i] <= 122)  )
        {
            sum++;
        }
    }
    return sum;
}


int how_many_words(string text)
{
    int sum = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            sum++;
        }
    }
    return sum + 1;
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






