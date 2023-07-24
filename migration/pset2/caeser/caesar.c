#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool validate(string number);
string cipher(int key, string text);



int main(int argc, string argv[])
{
    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (validate(argv[1]))
    {
        printf("success\n");
        int key = atoi(argv[1]);
        string text = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int i = 0; i < strlen(text); i++)
        {
            if (isalpha(text[i]) && isupper(text[i]))
            {
                printf("%c", (text[i] - 65 + key) % 26 + 65 );
            }
            else if (isalpha(text[i]) && islower(text[i]))
            {
                printf("%c", (text[i] - 97 + key) % 26 + 97);
            }
            else
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");

    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
}

bool validate(string number)
{
    for (int  i = 0; i < strlen(number); i++)
    {
        if ((number[i] < 48) || (number[i] > 57))
        {
            return 1;
            return false;
            break;
        }
    }
    return true;
}

string cipher(int key, string text)
{
    string ciphertext = "";
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            ciphertext[i] = (((int)text[i] - 97 + key) % 26) + 97;
        }
        else
        {
            ciphertext[i] = text[i];
        }
    }
    return ciphertext;
}



