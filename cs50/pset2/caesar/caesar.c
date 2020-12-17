#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    string text = get_string("plaintext:");
    printf("ciphertext:");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char newletter;
        if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
        else
        {
            if (isupper(text[i]))
            {
                newletter = text[i] - 'A';
                newletter += atoi(argv[1]);
                newletter = newletter % 26;
                text[i] = newletter + 'A';
                printf("%c", text[i]);
            }
            else if (islower(text[i]))
            {
                newletter = text[i] - 'a';
                newletter += atoi(argv[1]);
                newletter = newletter % 26;
                text[i] = newletter + 'a';
                printf("%c", text[i]);
            }
        }
    }
    printf("\n");
}