#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

string text;
void verify(string input);
int count_letters(string input);
int count_sentences(string input);
int count_words(string input);
void get_level(int l, int w, int s);

int main(void)
{
    text = get_string("Text: ");
    verify(text);

}

void verify(string input)
{
    count_letters(input);
    count_sentences(input);
    count_words(input);
    get_level(count_letters(input), count_words(input), count_sentences(input));

}

int count_letters(string input)
{
    int letters = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isalpha(input[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_sentences(string input)
{

    int sentences = 0;

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        int c = input[i];
        if (c == 33 || c == 46 || c == 63)
        {
            sentences++;
        }
    }
    return sentences;
}

int count_words(string input)
{

    int words = 1;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        int c = input[i];
        if (isspace(c))
        {
            words++;
        }
    }
    return words;
}

void get_level(int l, int w, int s)
{
    float L = (l / (float) w) * 100;
    float S = (s / (float) w) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}