#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string key;
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        for (int j = i + 1; j < n; j++)
        {
            if (tolower(argv[1][i]) == tolower(argv[1][j]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
        argv[1][i] = tolower(argv[1][i]);
    }
    key = argv[1];
    string text = get_string("plaintext:");
    printf("ciphertext:");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int original_index;
        if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
        else
        {
            if (isupper(text[i]))
            {
                original_index = text[i] - 'A';
                text[i] = toupper(key[original_index]);
                printf("%c", text[i]);
            }
            else if (islower(text[i]))
            {
                original_index = text[i] - 'a';
                text[i] = key[original_index];
                printf("%c", text[i]);
            }
        }
    }
    printf("\n");
    return 0;
}