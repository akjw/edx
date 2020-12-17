#include <cs50.h>
#include <stdio.h>


bool validated(long card);
int get_length(long card);
bool checksum(long card);
void checkType(long card);

int main(void)
{
    long credit_number;

    do
    {
        credit_number = get_long("Number: ");
    }
    while (credit_number < 0);

    if (validated(credit_number) == true)
    {
        checkType(credit_number);
    }
    else
    {
        printf("INVALID\n");
    }
}


bool validated(long card)
{
    // get length of card number
    int len = get_length(card);
    return (len == 13 || len == 15 || len == 16) && checksum(card);
}

int get_length(long card)
{
    int length;
    for (length = 0; card != 0; card /= 10, length++);
    return length;
}

bool checksum(long card)
{
    int total = 0;
    int digit;
    for (int i = 0; card != 0; i++, card /= 10)
    {
        if (i % 2 == 0)
        {
            // add sum to sum of remaining numbers
            total += card % 10;
        }
        else
        {
            // multiply every other number by 2
            digit = 2 * (card % 10);
            // add digits of every product + qdd to sum
            total += digit % 10 + digit / 10;
        }
    }
    // check final digit = 0
    return (total % 10) == 0;
}

void checkType(long card)
{
    if ((card >= 34e13 && card < 35e13) || (card >= 37e13 && card < 38e13))
    {
        printf("AMEX\n");
    }
    else if (card >= 51e14 && card < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((card >= 4e12 && card < 5e12) || (card >= 4e15 && card < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}