#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool checkrepeat(string key);
bool validate(string key);
void ciphertext(string key, string text);



int main(int argc, string argv[])
{
    if ((argc == 2 && strlen(argv[1]) == 26) && (validate(argv[1]) && checkrepeat(argv[1])))
    {
        string key = argv[1];
        printf("succeed\n");
        string text = get_string("plain text: ");
        ciphertext(key, text);

    }
    else if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        printf("uncorrect key\n");
        return 1;
    }
}

bool validate(string key)
{
    int m = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        if (!(isalpha(key[i])))
        {
            m++;
        }
    }
    if (m == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkrepeat(string key)
{
    int m = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = 0; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                m++;
            }
        }
    }
    if (m == 26)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ciphertext(string key, string text)
{
    printf("ciphertext: ");
    for (int i = 0; i < strlen(text); i++)
    {

        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                printf("%c", tolower(key[(int)text[i] - 97]));
            }
            if (isupper(text[i]))
            {
                printf("%c", toupper(key[(int)text[i] - 65]));
            }
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}












